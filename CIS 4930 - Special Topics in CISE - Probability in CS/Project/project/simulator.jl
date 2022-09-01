import Pkg
Pkg.add(["DataStructures", "Distributions", "LinearAlgebra", "ProgressBars", "ResumableFunctions","Statistics", "SimJulia"])
using DataStructures, Distributions, LinearAlgebra, Logging, ProgressBars, Statistics, StatsBase
using ResumableFunctions, SimJulia

# Debugger
#region
debug_logger = Logging.ConsoleLogger(stderr, Logging.Debug)
simple_logger = Logging.SimpleLogger(open("log.txt", "w+"))
Logging.global_logger(debug_logger)
# Logging.disable_logging(Logging.Error)
#endregion

# Data Structures and Other Variables
#region
# holds requests from user as pairs (file index, timestamp of request)
# DO NOT confuse with FIFO queue for access link, which is not actually implemented
# since only the head of queue is important
requests = DataStructures.Queue{Pair{Int64, Int64}}()
buffer = DataStructures.Queue{Pair{Int64, Int64}}() # FIFO queue right before access link
trait = Dict([])
cache = DataStructures.PriorityQueue{Int64, Float64}() # priorty queue for cache

S = Array{Float64, 1}() # file sizes
P = Array{Float64, 1}() # file popularities

# How to order files in cache
@enum ReplacementPolicy begin
    OldestFirst = 1
    LeastPopularFirst = 2
    LargestFirst = 3
    LeastFrequentlyUsed = 4
    Clock = 5
end
#endregion

# Functions
#region
"""
Computes priority of file based on replacement policy.

...
# Arguments
- `file::Int64`: 1-based index of file in S.
- `policy::ReplacementPolicy`: Strategy to update cache when capacity is breached.
...
"""
function priority(file::Int64, policy::ReplacementPolicy)::Float64
    @info "ENTER [priority]:\n(\nfile = $file,\npolicy = $policy\n)\n"

    global trait = trait
    @assert file >= 1 "File must have index greater than or equal to 1"
    # Note: Only guaranteed valid for file at front of buffer (queue)
    if policy in [OldestFirst, LeastFrequentlyUsed, Clock]
        return trait[file]
    elseif policy == LeastPopularFirst
        return floor(P[file] * 1000)
    elseif policy == LargestFirst
        return -S[file]
    end
end

"""
Sets priority of file based on replacement policy.

...
# Arguments
- `file::Int64`: 1-based index of file in S.
- `value::Any`: New priorty.
- `policy::ReplacementPolicy`: Strategy to update cache when capacity is breached.
...
"""
function setpriority(file::Int64, value::Any, policy::ReplacementPolicy)
    @info "ENTER [setpriority]:\n(\nfile = $file,\nvalue = $value,\npolicy = $policy\n)\n"

    global trait = trait
    global cache = cache

    @assert file >= 1 "File must have index greater than or equal to 1"
    # Note: Only guaranteed valid for file at front of buffer (queue)
    if policy == OldestFirst
        # use timestamp as value so that smallest timestamp is oldest
        trait[file] = value
    elseif policy == LeastFrequentlyUsed
        # value in trait is counter that gets incremented during cache access or insertion being 0
        trait[file] = haskey(trait, file) ? trait[file] + 1 : 0
    elseif policy == Clock
        # only one file in trait can be 0, which cycles through all files in cache clockwise
        # all other entries have priorty 1
        if !haskey(trait, file)
            trait[file] = 1
        end

        keyed_files::Vector{Int64} = collect(keys(trait))
        idx = findfirst(f -> trait[f] == 0, keyed_files)
        if isnothing(idx)
            trait[keyed_files[1]] = 0
        else
            trait[keyed_files[idx]] = 1
            trait[keyed_files[idx == length(keyed_files) ? 1 : idx + 1]] = 0
        end
    end

    # udpate priority queue
    for keyed_file in collect(keys(trait))
        if haskey(cache, keyed_file)
            cache[keyed_file] = trait[keyed_file]
        end
    end
end

#endregion

# Simulation
#region
"""
Computes priority of file based on replacement policy.

...
# Arguments
- `max_time::Int64`: The time limit to run events; any response times that end at a time point after are disregarded.
- `N::Int64=10000`: The number of available files to request.
- `r_a::T=15`: The access link bandwidth (MB).
- `r_c::T=1000`: The institutional bandwidth when fetching from cache.
- `lambda::T=1`: Poisson process mean to determine number of new requests sent during some step.
- `mu::T=1`: Pareto distribution mean to determine file size and popularity samples.
- `C::Union{T, Nothing}=nothing`: Cache capacity. If left defaulted to `nothing`, then C automatically becomes 0.10 of total size of N files (MB).
- `policy::ReplacementPolicy=OldestFirst`: Replacement policy for cache when adding new file to cache requires deleting existing cached files.
- `verbose::Bool`: Whether to print metadata.
...
"""
function simulate(
    # required params
    max_time::Int64;

    # optional params
    N::Int64=10000,
    r_a::T=15,
    r_c::T=1000,
    lambda::T=1,
    mu::T=1, 
    C::T=0.10,
    policy::ReplacementPolicy=OldestFirst,
    verbose::Bool=false
) where {T <: Real}
    # validity checks
    @assert max_time >= 1 "max_time ($max_time) must be greater than or equal to 1."
    @assert N >= 1000 "N must be very large, being greater than or equal to 1000."

    # global variables
    #region
    global requests = requests
    global buffer = buffer
    global trait = trait
    global cache = cache
    global S = S
    global P = P
    #endregion

    # Probability Distributions and Sampled Data
    #region
    # files are identified simply by 1-based index in S with S[i] being size for the i^th file (S_i)
    F_s = Distributions.Pareto(mu, 1)
    S = rand(F_s, N)
    F_p = Distributions.Pareto(mu, 1)
    P_raw = rand(F_p, N)
    P = LinearAlgebra.normalize(P_raw, 1)
    U_n = Distributions.Poisson(lambda) # models inter-arrival time between user requests
    D = Distributions.LogNormal() # round-trip time
    #endregion

    #validity checks
    # C = if isnothing(C) max(minimum(S), floor(Int64, sum(S) / 10)) else C end
    @assert C > 0 "C ($C) cannot be negative."
    C = C < 1 ? C * sum(S) : C
    @assert C >= minimum(S) "C ($C) cannot even hold the smallest file available."
    @assert length(S) == N "Length of file sizes (S) must be equal to $N (parameter N) but is actually $(length(S))."
    @assert length(P) == N "Length of file popularities (P) must be equal to $N (parameter N) but is actually $(length(P))."

    # Display Metadata
    #region
    if verbose
        @info "Total number of unique files requestable (N): $N"
        @info "Bandwidth of access link (r_a): $r_a"
        @info "Bandwith within institutional network (r_c): $r_c"
        @info "Poisson process rate for user requests per second (lambda): $lambda"
        @info "Capacity of cache (MB) (C): $C"

        @info "File size distribution (F_s): $F_s"
        # println("Sizes of files (S): $S")
        @info "Popularity distribution (F_p): $F_p"
        # println("Popularity (P_raw): $P_raw")
        # println("Popularity normalized (P): $P")
    end
    #endregion

    cache_size::Float64 = 0 # total MB used so far by cache
    ts::Int64 = 1 # keeps track of time steps, as integer seconds
    mru_request_ts::Int64 = 0 # most recently used timestamp for user request
    response_time::Float64 = 0 # response time to completely send a file to user
    response_time_all::Vector{Float64} = Vector{Float64}() # collection of repsonse times for all requested files

    for ts_cont in 1:max_time
        # ProgressBars.ProgressBar(1:max_time)
        # purpose is for progress bar only
        if ts_cont != ts
            continue
        end

        @info repeat("-", 100)
        @info "Time Step: $ts"

        # add new requests from lagged time interval
        while(mru_request_ts <= ts)
            inter_arrival_time::Int64 = rand(U_n)
            sampled_file = StatsBase.sample(1:N, Weights(P))
            mru_request_ts += inter_arrival_time
            enqueue!(requests, Pair(sampled_file, mru_request_ts))
            setpriority(sampled_file, mru_request_ts, policy)

            @debug "[$mru_request_ts] new-request-event:\nfile: $sampled_file"
            Logging.global_logger(simple_logger)
            @debug "[$mru_request_ts] new-request-event:\nfile: $sampled_file"
            Logging.global_logger(debug_logger)
        end

        # index of next-in-line requested file
        @info "Fetching requests."    
        file::Int64, timestamp::Int64 = dequeue!(requests)

        # check inside cache first
        if haskey(cache, file)
            @info "File already in cache."
            response_time = S[file] / r_c
            push!(response_time_all, response_time)
            setpriority(file, timestamp, policy)
            
            @debug "[$ts + $response_time] file-received-event:\nfile: $file\nresponse time: $response_time"
            with_logger(simple_logger) do
                @debug "[$ts + $response_time] file-received-event:\nfile: $file\nresponse time: $response_time"
            end
        else
            # not in cache
            @info "File not in cache."

            # compute time delay components
            round_trip_time::Float64 = rand(D)
            @debug "round_trip_time: $round_trip_time"
            @debug "[$ts + $round_trip_time] arrive-at-queue-event:\nfile: $file"
            Logging.global_logger(simple_logger)
            @debug "[$ts + $round_trip_time] arrive-at-queue-event:\nfile: $file"
            Logging.global_logger(debug_logger)

            enqueue!(buffer, Pair(file, timestamp))
            if isempty(buffer)
                @debug "Buffer empty, so dequeue immediately for same file."
            else
                @debug "Buffer not empty, so pushing current request to back."
                @debug "File swapped from $file to $(first(first(buffer))), so pushing current request to back."
            end

            while !isempty(buffer)
                top::Pair{Int64, Int64} = dequeue!(buffer)
                file = first(top)
                timestamp = last(top)
                access_link_delay::Float64 = S[file] / r_a

                @debug "access_link_delay: $access_link_delay"
                @debug "[$ts + $access_link_delay] depart-queue-event:\nfile: $file"
                Logging.global_logger(simple_logger)
                @debug "[$ts + $access_link_delay] depart-queue-event:\nfile: $file"
                Logging.global_logger(debug_logger)

                cache_transmission_delay::Float64 = S[file] / r_c
                response_time = round_trip_time + access_link_delay + cache_transmission_delay
                @debug "[$ts + $response_time] file-received-event:\nfile: $file\nresponse time: $response_time"
                Logging.global_logger(simple_logger)
                @debug "[$ts + $response_time] file-received-event:\nfile: $file\nresponse time: $response_time"
                Logging.global_logger(debug_logger)

                push!(response_time_all, response_time)
                ts += ceil(Int64, response_time)

                # update cache with file
                @info "Updating cache."
                old_cache_size::Float64 = cache_size
                
                # reconfiguring priorities if need be
                try
                    if S[file] <= C
                        # remove extraneous files from cache when capacity exceeded
                        @warn "Removing lowest priority files from priority queue to make room for file $file with size $(S[file])."
                        cache_size += S[file]
                        while cache_size > C
                            d_file::Int64, priority::Float64 = dequeue!(cache)
                            @warn "Removing file $d_file from priority queue."
                            cache_size -= S[d_file]
                            delete!(trait, d_file)
                        end
                        setpriority(file, timestamp, policy)
                        file_priority::Float64 = priority(file, policy)
                        @debug "Enqueue file to cache with priority: $file_priority"
                        if cache_size != old_cache_size
                            @debug "Cache size net change after replacements: $(cache_size - old_cache_size)"
                        end
                    else
                        @warn "File $file with size $(S[file]) is larger than cache capacity."
                    end
                catch error
                    continue
                end
            end
        end
        # clean up after executing requests for this step

    end
    #endregion

    # cleanup of global variables
    empty!(requests)
    empty!(buffer)
    empty!(trait)
    empty!(cache)

    mean_response_time = Statistics.mean(response_time_all)
    @debug "Collected response times: $response_time_all"
    @debug "Mean response_time: $mean_response_time"

    return mean_response_time
end
