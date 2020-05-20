
# https://docs.python.org/3.8/library/os.html
import os

# exception os.error
# An alias for the built-in OSError exception.
os.error('YEET!')

# os.name
# The name of the operating system dependent module imported. The following names have currently been registered:
# 'posix', 'nt', 'java'.
print(f'OS name: {os.name}')

########################################################################################################################
# PROCESS PARAMETERS
# os.ctermid()
# Return the filename corresponding to the controlling terminal of the process.
print(f'Controlling terminal id: {os.ctermid()}')

# os.environ
# A mapping object representing the string environment.
print(f'String environment: {os.environ}')

# os.environb
# Bytes version of environ: a mapping object representing the environment as byte strings. environ and environb are
# synchronized (modify environb updates environ, and vice versa).
print(f'String environment (byte): {os.environb}')

# os.fsencode(filename)
# Encode path-like filename to the filesystem encoding with 'surrogateescape' error handler, or 'strict' on Windows;
# return bytes unchanged.
desktop_path = '/Users/fennec2000/Desktop/'
encoded_filename = os.fsencode(filename=desktop_path)
print(f'Encoded filename: {encoded_filename}')

# os.fsdecode(filename)
# Decode the path-like filename from the filesystem encoding with 'surrogateescape' error handler, or 'strict' on Windows;
# return str unchanged.
decoded_filename = os.fsdecode(filename=encoded_filename)
print(f'Decoded filename: {decoded_filename}')

# os.fspath(path)¶
# Return the file system representation of the path.
# If str or bytes is passed in, it is returned unchanged. Otherwise __fspath__() is called and its value is returned as
# long as it is a str or bytes object. In all other cases, TypeError is raised.
fs_path = os.fspath(path=desktop_path)
print(f'Filesystem representation of path: {fs_path}')

########################################################################################################################
# class os.PathLike

# os.getenv(key, default=None)
# Return the value of the environment variable key if it exists, or default if it doesn’t. key, default and the result
# are str.
print(os.getenv(key='fennec2000'))

# os.getenvb(key, default=None)
# Return the value of the environment variable key if it exists, or default if it doesn’t. key, default and the result
# are bytes.
print(f'OS supports bytes environ? {os.supports_bytes_environ}')
# print(os.getenvb())

# os.get_exec_path(env=None)
# Returns the list of directories that will be searched for a named executable, similar to a shell, when launching a
# process. env, when specified, should be an environment variable dictionary to lookup the PATH in. By default, when env
# is None, environ is used.
PATH_variables = os.get_exec_path(env=None)
print(f'PATH variables: \n{PATH_variables}')

# os.access(path, mode, *, dir_fd=None, effective_ids=False, follow_symlinks=True)
# Use the real uid/gid to test for access to path.
print(f'Supports effective ids? {os.supports_effective_ids}')
print(f"User access to desktop: {os.access(path='/Users/fennec2000/Desktop/', mode=os.F_OK, effective_ids=False, follow_symlinks=True)}")

# os.getegid()
# Return the effective group id of the current process. This corresponds to the “set id” bit on the file being executed in
# the current process.
print(f'Effective group id of current process: {os.getegid()}')

# os.geteuid()
# Return the current process’s effective user id.
print(f'Effective user id of current process: {os.geteuid()}')

# os.getgid()
# Return the real group id of the current process.
print(f'Group id of current process: {os.getgid()}')

# os.getgrouplist(user, group)
# Return list of group ids that user belongs to. If group is not in the list, it is included; typically, group is
# specified as the group ID field from the password record for user.
print(f"Groups user (root) belongs to: {os.getgrouplist}")

# os.getgroups()
# Return list of supplemental group ids associated with the current process.
print(f'Groups associated with current process: {os.getgroups()}')

# os.getlogin()
# Return the name of the user logged in on the controlling terminal of the process. For most purposes, it is more useful
# to use getpass.getuser() since the latter checks the environment variables LOGNAME or USERNAME to find out who the user
# is, and falls back to pwd.getpwuid(os.getuid())[0] to get the login name of the current real user id.
print(f'User logged in: {os.getlogin()}')

# os.getpgid(pid)
# Return the process group id of the process with process id pid. If pid is 0, the process group id of the current process
# is returned.
print(f'Group id of specific process (given pid): {os.getpgid(pid=81659)}')

# os.getpgrp()
# Return the id of the current process group.
print(f'Current process group id: {os.getpgrp()}')

# os.getpid()
# Return the current process id.
print(f'Current process id: {os.getpid()}')

# os.getppid()
# Return the parent’s process id. When the parent process has exited, on Unix the id returned is the one of the init
# process (1), on Windows it is still the same id, which may be already reused by another process.
print(f'Parent process id: {os.getppid()}')

# os.getpriority(which, who)
# Get program scheduling priority. The value which is one of PRIO_PROCESS, PRIO_PGRP, or PRIO_USER, and who is interpreted
# relative to which (a process identifier for PRIO_PROCESS, process group identifier for PRIO_PGRP, and a user ID for PRIO_USER).
# A zero value for who denotes (respectively) the calling process, the process group of the calling process, or the real user ID of the calling process.
print(f'Priority process: {os.getpriority(which=os.PRIO_PROCESS, who=0)}')

# os.getresuid()
# Return a tuple (ruid, euid, suid) denoting the current process’s real, effective, and saved user ids.
# print(f'real, effective, and stored user ids: {os.getresuid()}')

# os.getresgid()
# Return a tuple (rgid, egid, sgid) denoting the current process’s real, effective, and saved group ids.
print(f'real, effective, and stored group ids: {os.getresgid()}')

# os.getuid()
# Return the current process’s real user id.
print(f'User id of current process: {os.getuid()}')

# os.initgroups(username, gid)
# Call the system initgroups() to initialize the group access list with all of the groups of which the specified username
# is a member, plus the specified group id.
os.initgroups(username='fennec2000', gid=os.getgid())

# os.putenv(key, value)
# Set the environment variable named key to the string value. Such changes to the environment affect subprocesses started
# with os.system(), popen() or fork() and execv().

# os.setegid(egid)
# Set the current process’s effective group id.
os.setegid(__egid=20)

# os.seteuid(euid)
# Set the current process’s effective user id.
os.seteuid(__euid=2)

# os.setgid(gid)
# Set the current process’ group id.
os.setgid(__gid=10)

# os.setgroups(groups)
# Set the list of supplemental group ids associated with the current process to groups. groups must be a sequence, and
# each element must be an integer identifying a group. This operation is typically available only to the superuser.

# os.setpgrp()
# Call the system call setpgrp() or setpgrp(0, 0) depending on which version is implemented (if any). See the Unix manual for the semantics.
os.setpgrp()

# os.setpgid(pid, pgrp)
# Call the system call setpgid() to set the process group id of the process with id pid to the process group with id pgrp.
# See the Unix manual for the semantics.
os.setpgid(__pid=12, __pgrp=120)

# os.setpriority(which, who, priority)
# Set program scheduling priority. The value which is one of PRIO_PROCESS, PRIO_PGRP, or PRIO_USER, and who is interpreted
# relative to which (a process identifier for PRIO_PROCESS, process group identifier for PRIO_PGRP, and a user ID for PRIO_USER). A zero value for who denotes (respectively) the calling process, the process group of the calling process, or the real user ID of the calling process. priority is a value in the range -20 to 19. The default priority is 0; lower priorities cause more favorable scheduling.

# os.setregid(rgid, egid)
# Set the current process’s real and effective group ids.
os.setregid(__rgid=1, __egid=2)

# os.setresgid(rgid, egid, sgid)
# Set the current process’s real, effective, and saved group ids.
os.setresgid(rgid=10, egid=20, sgid=30)

# os.setresuid(ruid, euid, suid)
# Set the current process’s real, effective, and saved user ids.
os.setresuid(ruid=0, euid=1, suid=2)

# os.setreuid(ruid, euid)
# Set the current process’s real and effective user ids.
os.setreuid(__ruid=0, __euid=1)

# os.strerror(code)
# Return the error message corresponding to the error code in code. On platforms where strerror() returns NULL when given
# an unknown error number, ValueError is raised.
print(f'Error message from error code: {os.strerror(__code=0)}')

# os.umask(mask)
# Set the current numeric umask and return the previous umask.

# os.uname()
# Returns information identifying the current operating system. The return value is an object with five attributes:
#     sysname - operating system name
#     nodename - name of machine on network (implementation-defined)
#     release - operating system release
#     version - operating system version
#     machine - hardware identifier
os_information = os.uname()
print(f'Operating system specs: \n{os_information}')

# os.unsetenv(key)
# Unset (delete) the environment variable named key. Such changes to the environment affect subprocesses started with os.system(), popen() or fork() and execv().

# os.stat(path, *, dir_fd=None, follow_symlinks=True)
# Get the status of a file or a file descriptor. Perform the equivalent of a stat() system call on the given path. path
# may be specified as either a string or bytes – directly or indirectly through the PathLike interface – or as an open file descriptor. Return a stat_result object.
print(os.stat(path='/Users/fennec2000/Desktop/', dir_fd=True, follow_symlinks=True))

########################################################################################################################
# FILES AND DIRECTORIES
# most important functions

print(f'Current directory: {os.getcwd()}')

os.chdir(path='/Users/fennec2000/Desktop/Summer 2020/CIS 4930 - Special Topics - Performant Programming in Python/')

print(os.listdir())

# os.mkdir(path='~/Desktop/Summer 2020/CIS 4930 - Special Topics - Performant Programming in Python/PythonCrashCourse/src/',
#          mode=os.F_OK,
#          )
