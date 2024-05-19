#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    time_t now = time(NULL);
    struct tm *utc = gmtime(&now);

    int t = 0;
    char *format = NULL;
    char buffer[80];
    int opt;

    while ((opt = getopt(argc, argv, "t:f:")) != -1) {
        switch (opt) {
            case 't':
                t = atoi(optarg);
                continue;
            case 'f':
                format = optarg;
                continue;
            default:
                fprintf(stderr, "Usage: %s [-t timezone] [-f format]\n", argv[0]);
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

