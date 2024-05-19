#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


void help(char *name) {
    printf("Usage: %s [OPTIONS]\n", name);
    printf("\n");
    printf("Options:\n");
    printf("  -t <timezone>  Timezone offset in hours\n");
    printf("  -f <format>    Output format (default: @%%06.2f)\n");
    printf("  -l             Use local time instead of UTC\n");
    printf("\n");
    printf("Examples:\n");
    printf("  %s\n", name);
    printf("  %s -t 3\n", name);
    printf("  %s -t -5 -f '%%06.2f'\n", name);
    printf("  %s -l\n", name);
    printf("\n");
    printf("Report bugs to: crg@crg.eti.br\n");
}




int main(int argc, char *argv[]) {
    time_t now = time(NULL);
    struct tm *utc = gmtime(&now);

    int t = 0;
    char *format = NULL;
    char buffer[80];
    int opt;

    while ((opt = getopt(argc, argv, "t:f:lh")) != -1) {
        switch (opt) {
            case 't':
                t = atoi(optarg);
                continue;
            case 'f':
                format = optarg;
                continue;
            case 'l':
                utc = localtime(&now);
                continue;
            case 'h':
                help(argv[0]);
                return 0;
            default:
                help(argv[0]);
                return 1;
        }
    }

    if (t < -12 || t > 12) {
        fprintf(stderr, "Invalid timezone\n");
        return 1;
    } 

    // Adjust hour with timezone and normalize to [0, 23]
    int adjusted_hour = (utc->tm_hour + t + 24) % 24;

    // Calculate the beat value (Swatch Internet Time)
    int total_seconds_bmt = adjusted_hour * 3600 + utc->tm_min * 60 + utc->tm_sec;
    float beat = total_seconds_bmt / 86.4;  // 1 day = 1000 beats so 1 beat = 86.4 seconds

    if (format == NULL) {
        format = "@%06.2f\n";
    }

    printf(format, beat);

    return 0;
}

