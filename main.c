#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    time_t now = time(NULL);
    struct tm *utc = gmtime(&now);

    // Calculate the beat value (Swatch Internet Time)
    int total_seconds_bmt =
        ((utc->tm_hour + 1) % 24) * 3600 + utc->tm_min * 60 + utc->tm_sec;

    float beat = total_seconds_bmt /
                 86.4;  // 1 day = 1000 beats so 1 beat = 86.4 seconds

    if (argc == 2) {
        printf(argv[1], beat);
        return 0;
    }

    printf("@%.2f\n", beat);

    return 0;
}

