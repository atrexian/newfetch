#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <pwd.h>

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define ORANGE "\033[1;38;5;208m"
#define TEAL "\033[1;38;5;30m"
#define LIME "\033[1;38;5;118m"
#define MINT "\033[1;38;5;48m"

const char *arch_logo[] = {
    "         /\\        ",
    "        /  \\       ",
    "       /\\   \\     ",
    "      /      \\     ",
    "     /   ,,   \\    ",
    "    /   |  |  -\\   ",
    "   /_-''    ''-_\\  "
};

const char *debian_logo[] = {
    "      _____       ",
    "     /  __ \\     ",
    "    |  /    |     ",
    "    |  \\___-     ",
    "    -_            ",
    "      --_         ",
    "                  ",
    "                  "
};

const char *ubuntu_logo[] = {
    "         _        ",
    "        ---(_)    ",
    "    _/  ---  \\   ",
    "   (_) |   |      ",
    "     \\  --- _/   ",
    "        ---(_)    ",
    "                  ",
    "                  "
};

const char *fedora_logo[] = {
    "        _____     ",
    "       /   __)\\  ",
    "       |  /  \\ \\",
    "    ___|  |__/ /  ",
    "   / (_    _)_/   ",
    "  / /  |  |       ",
    "  \\ \\__/  |     ",
    "   \\(_____/      "
};

const char *manjaro_logo[] = {
    "  ||||||||| ||||  ",
    "  ||||||||| ||||  ",
    "  ||||      ||||  ",
    "  |||| |||| ||||  ",
    "  |||| |||| ||||  ",
    "  |||| |||| ||||  ",
    "  |||| |||| ||||  "
};

const char *gentoo_logo[] = {
    "     _-----_      ",
    "    (       \\    ",
    "    \\    0   \\  ",
    "     \\        )  ",
    "     /      _/    ",
    "    (     _-      ",
    "    \\____-       "
};

const char *linuxmint_logo[] = {
    "  ___________     ",
    "  |_          \\  ",
    "    | | _____ |   ",
    "    | | | | | |   ",
    "    | | | | | |   ",
    "    | \\_____/ |  ",
    "    \\_________/  "
};

const char *opensuse_logo[] = {
    "    _______       ",
    "    __|   __ \\   ",
    "         / .\\ \\ ",
    "         \\__/ |  ",
    "       _______|   ",
    "       \\_______  ",
    "    __________/   "
};

const char *void_logo[] = {
    "      _______     ",
    "   _ \\______ -   ",
    "  | \\  ___  \\ | ",
    "  | | /   \\ | |  ",
    "  | | \\___/ | |  ",
    "  | \\______ \\_| ",
    "   -_______\\     "
};

const char *tux_logo[] = {
    "        .--.      ",
    "       |o_o |     ",
    "       |:_/ |     ",
    "      //   \\ \\  ",
    "     (|     | )   ",
    "    /'\\_   _/`\\ ",
    "    \\___)=(___/  "
};

typedef struct {
    const char *name;
    const char **logo;
    int logo_lines;
    const char *ascii_color;
    const char *text_color;
} DistroInfo;

const DistroInfo distros[] = {
    { "arch",      arch_logo,      sizeof(arch_logo)/sizeof(arch_logo[0]),       CYAN,    CYAN },
    { "debian",    debian_logo,    sizeof(debian_logo)/sizeof(debian_logo[0]),   RED,     RED },
    { "ubuntu",    ubuntu_logo,    sizeof(ubuntu_logo)/sizeof(ubuntu_logo[0]),   ORANGE,  ORANGE },
    { "fedora",    fedora_logo,    sizeof(fedora_logo)/sizeof(fedora_logo[0]),   BLUE,    BLUE },
    { "manjaro",   manjaro_logo,   sizeof(manjaro_logo)/sizeof(manjaro_logo[0]), TEAL,    TEAL },
    { "gentoo",    gentoo_logo,    sizeof(gentoo_logo)/sizeof(gentoo_logo[0]),   MAGENTA, MAGENTA },
    { "linux mint",linuxmint_logo, sizeof(linuxmint_logo)/sizeof(linuxmint_logo[0]), LIME, LIME },
    { "opensuse",  opensuse_logo,  sizeof(opensuse_logo)/sizeof(opensuse_logo[0]), LIME,  LIME },
    { "void",  void_logo,  sizeof(void_logo)/sizeof(void_logo[0]), MINT,  MINT }
};

const DistroInfo* find_distro_info(const char *distro_name) {
    for (size_t i = 0; i < sizeof(distros)/sizeof(distros[0]); ++i) {
        if (strcasestr(distro_name, distros[i].name)) {
            return &distros[i];
        }
    }
    return NULL;
}

int main() {
    struct passwd *pw = getpwuid(getuid());
    char username[256] = "Unknown";
    if (pw) {
        strncpy(username, pw->pw_name, sizeof(username));
        username[sizeof(username)-1] = '\0';
    }

    char hostname[256] = "Unknown";
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        strncpy(hostname, "Unknown", sizeof(hostname));
    }

    struct utsname uts;
    if (uname(&uts) != 0) {
        fprintf(stderr, "uname error\n");
        return 1;
    }

    FILE *fp = fopen("/etc/os-release", "r");
    char distro[256] = "Unknown";
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            if (sscanf(line, "PRETTY_NAME=\"%[^\"]\"", distro) == 1) break;
        }
        fclose(fp);
    }

    const DistroInfo *info_ptr = find_distro_info(distro);

    const char **logo = tux_logo;
    int logo_lines = sizeof(tux_logo)/sizeof(tux_logo[0]);
    const char *ascii_color = YELLOW;
    const char *text_color = YELLOW;

    if (info_ptr) {
        logo = info_ptr->logo;
        logo_lines = info_ptr->logo_lines;
        ascii_color = info_ptr->ascii_color;
        text_color = info_ptr->text_color;
    }

    char info[10][256];
    snprintf(info[0], sizeof(info[0]), "%sUser:%s %s", text_color, RESET, username);
    snprintf(info[1], sizeof(info[1]), "%sHost:%s %s", text_color, RESET, hostname);
    snprintf(info[2], sizeof(info[2]), "%sDistro:%s %s", text_color, RESET, distro);
    snprintf(info[3], sizeof(info[3]), "%sKernel:%s %s %s", text_color, RESET, uts.sysname, uts.release);
    snprintf(info[4], sizeof(info[4]), "%sArchitecture:%s %s", text_color, RESET, uts.machine);

    FILE *uptime_fp = fopen("/proc/uptime", "r");
    double uptime_seconds = 0;
    if (uptime_fp) {
        fscanf(uptime_fp, "%lf", &uptime_seconds);
        fclose(uptime_fp);
    }
    int days = uptime_seconds / 86400;
    int hours = ((int)uptime_seconds % 86400) / 3600;
    int minutes = ((int)uptime_seconds % 3600) / 60;
    snprintf(info[5], sizeof(info[5]), "%sUptime:%s %d days, %d hours, %d mins", text_color, RESET, days, hours, minutes);

    FILE *cpu_fp = fopen("/proc/cpuinfo", "r");
    int cores = 0;
    char cpu_model[256] = "";
    if (cpu_fp) {
        char line[512];
        while (fgets(line, sizeof(line), cpu_fp)) {
            if (strncmp(line, "processor", 9) == 0) cores++;
            if (strncmp(line, "model name", 10) == 0 && cpu_model[0] == '\0') {
                char *colon = strchr(line, ':');
                if (colon) {
                    strncpy(cpu_model, colon + 2, sizeof(cpu_model) - 1);
                    cpu_model[sizeof(cpu_model) - 1] = '\0';
                    cpu_model[strcspn(cpu_model, "\n")] = '\0';
                }
            }
        }
        fclose(cpu_fp);
    }

    if (cpu_model[0] == '\0') {
        strncpy(cpu_model, "Unknown", sizeof(cpu_model));
    }

    snprintf(info[6], sizeof(info[6]), "%sCPU:%s %s (%d)", text_color, RESET, cpu_model, cores);

    FILE *mem_fp = fopen("/proc/meminfo", "r");
    unsigned long mem_total = 0, mem_free = 0, buffers = 0, cached = 0;
    if (mem_fp) {
        char line[256];
        while (fgets(line, sizeof(line), mem_fp)) {
            if (sscanf(line, "MemTotal: %lu kB", &mem_total) == 1) continue;
            if (sscanf(line, "MemFree: %lu kB", &mem_free) == 1) continue;
            if (sscanf(line, "Buffers: %lu kB", &buffers) == 1) continue;
            if (sscanf(line, "Cached: %lu kB", &cached) == 1) continue;
        }
        fclose(mem_fp);
    }

    unsigned long used = mem_total - mem_free - buffers - cached;
    float used_percent = 0;
    if (mem_total > 0)
        used_percent = (used / (float)mem_total) * 100;

    const char *ram_color = (used_percent > 80.0) ? RED :
                            (used_percent > 60.0) ? YELLOW : GREEN;

    snprintf(info[7], sizeof(info[7]), "%sMemory:%s %s%.2f%% used%s (%.2f MB / %.2f MB)",
             text_color, RESET, ram_color, used_percent, RESET, used / 1024.0, mem_total / 1024.0);

    int max_lines = logo_lines > 8 ? logo_lines : 8;
    for (int i = 0; i < max_lines; i++) {
        if (i < logo_lines) {
            printf("%s%-20s%s", ascii_color, logo[i], RESET);
        } else {
            printf("%-20s", " ");
        }
        if (i < 8) {
            printf("%s\n", info[i]);
        } else {
            printf("\n");
        }
    }

    return 0;
}