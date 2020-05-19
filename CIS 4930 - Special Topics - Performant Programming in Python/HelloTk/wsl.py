import os


def get_wsl_distro():
    if 'WSL_DISTRO_NAME' in os.environ:
        return os.environ['WSL_DISTRO_NAME']
    else:
        return None


def get_wsl_ip():
    if not get_wsl_distro():
        return None

    result = None
    with open("/etc/resolv.conf", "r") as resolv_file:
        result = resolv_file.readlines()[-1].split(' ')[1].strip()
        resolv_file.close()

    return result


def set_display_to_host(major = 0, minor = None):
    if get_wsl_distro():
        os.environ['DISPLAY'] = (get_wsl_ip() + ":%d" % major + (".%d" % minor if minor != None else ""))