include("simulator.jl")
using Pkg
Pkg.add("DataFrames")
using DataFrames

Logging.disable_logging(Logging.Error)
# if length(ARGS) > 0 && isequal(ARGS[1], "--no-debug") 
#     Logging.disable_logging(Logging.Error)
# end

C_vec = Vector{Float64}([10, 50, 100])

df = DataFrames.DataFrame()

# Performance Testing
#region
for policy in instances(ReplacementPolicy)
    # ProgressBars.ProgressBar(instances(ReplacementPolicy)[1:3])
    global df = df
    global C_vec = C_vec
    results = Vector{Float64}()
    println("policy: $policy")

    for C in C_vec
        println("C: $C")
        while true
            try
                mean_response_time::Float64 = simulate(100; C=C, policy=policy, verbose=true)
                println("Mean response_time: $mean_response_time")
                append!(results, mean_response_time)
                break
            catch error
                continue
            end
        end
    end
    df[!, Symbol(string(policy))] = copy(results)
end

println(df)
#endregion
