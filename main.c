#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void convert_beats_to_time(float beats) {
    if (beats < 0 || beats >= 1000) {
        printf("Invalid beats value. Must be between 0 and 999.99\n");
        return;
    }

    float total_seconds = beats * 86.4;
    int hours = (int)(total_seconds / 3600);
    int minutes = (int)((total_seconds - hours * 3600) / 60);
    int seconds = (int)(total_seconds - hours * 3600 - minutes * 60);

    printf("@%.2f = %02d:%02d:%02d BMT (Biel Mean Time)\n", beats, hours,
           minutes, seconds);
}

void show_internet_date(struct tm *tm_ptr) {
    // Internet date format: day of year in beats
    int day_of_year = tm_ptr->tm_yday + 1;
    printf("Internet Date: %d.%03d (Year %d, Day %d)\n", tm_ptr->tm_year + 1900,
           day_of_year, tm_ptr->tm_year + 1900, day_of_year);
}

void verbose_output(float beat, struct tm *tm_ptr, int timezone_offset,
                    int use_local) {
    printf("=== Internet Time Details ===\n");
    printf("Current Beat: @%.2f\n", beat);
    printf("Standard Time: %02d:%02d:%02d\n", tm_ptr->tm_hour, tm_ptr->tm_min,
           tm_ptr->tm_sec);
    printf("Date: %04d-%02d-%02d\n", tm_ptr->tm_year + 1900, tm_ptr->tm_mon + 1,
           tm_ptr->tm_mday);

    if (use_local) {
        printf("Time Base: Local time\n");
    } else {
        printf("Time Base: UTC%+d\n", timezone_offset);
    }

    show_internet_date(tm_ptr);

    // Beat ranges
    if (beat < 250) {
        printf("Period: Morning beats (0-249)\n");
    } else if (beat < 500) {
        printf("Period: Afternoon beats (250-499)\n");
    } else if (beat < 750) {
        printf("Period: Evening beats (500-749)\n");
    } else {
        printf("Period: Night beats (750-999)\n");
    }
}

void help(char *name) {
    printf("Usage: %s [OPTIONS]\n", name);
    printf("\n");
    printf("Options:\n");
    printf("  -t <timezone>  Timezone offset in hours (-12 to +14)\n");
    printf("  -f <format>    Output format (default: @%%06.2f)\n");
    printf("  -l             Use local time instead of UTC\n");
    printf("  -b <beats>     Convert beats to standard time\n");
    printf("  -d             Show date in Internet Time format\n");
    printf("  -v             Verbose output with additional info\n");
    printf("  -w             Watch mode (continuous output)\n");
    printf("  -h             Show this help\n");
    printf("\n");
    printf("Format specifiers:\n");
    printf("  %%f   - Float beats (e.g., 347.22)\n");
    printf("  %%d   - Integer beats (e.g., 347)\n");
    printf("  %%3d  - Padded integer beats (e.g., 347)\n");
    printf("  %%04d - Zero-padded integer beats (e.g., 0347)\n");
    printf("\n");
    printf("Examples:\n");
    printf("  %s                    # Current Internet Time\n", name);
    printf("  %s -t 3               # Internet Time +3 hours\n", name);
    printf("  %s -f '%%04.0f'        # Zero-padded integer format\n", name);
    printf("  %s -l                 # Use local time\n", name);
    printf("  %s -b 500             # Convert 500 beats to standard time\n",
           name);
    printf("  %s -d                 # Show date\n", name);
    printf("  %s -v                 # Verbose output\n", name);
    printf("  %s -w                 # Watch mode\n", name);
    printf("\n");
    printf("About Internet Time:\n");
    printf("  Internet Time divides the day into 1000 beats.\n");
    printf("  Each beat equals 1 minute and 26.4 seconds.\n");
    printf("  Time is universal (no time zones in beat time).\n");
    printf("\n");
    printf("Report bugs to: crg@crg.eti.br\n");
}

int main(int argc, char *argv[]) {
    time_t now = time(NULL);
    struct tm *time_ptr = NULL;

    int t = 0;
    char *format = NULL;
    int opt;
    int use_local = 0;
    int show_date = 0;
    int verbose = 0;
    int watch_mode = 0;
    float convert_beats = -1;

    while ((opt = getopt(argc, argv, "t:f:lb:dvwh")) != -1) {
        switch (opt) {
            case 't':
                t = atoi(optarg);
                continue;
            case 'f':
                format = optarg;
                continue;
            case 'l':
                use_local = 1;
                continue;
            case 'b':
                convert_beats = atof(optarg);
                continue;
            case 'd':
                show_date = 1;
                continue;
            case 'v':
                verbose = 1;
                continue;
            case 'w':
                watch_mode = 1;
                continue;
            case 'h':
                help(argv[0]);
                return 0;
            default:
                help(argv[0]);
                return 1;
        }
    }

    // Handle beat conversion mode
    if (convert_beats >= 0) {
        convert_beats_to_time(convert_beats);
        return 0;
    }

    if (t < -12 || t > 14) {  // Extended range for timezone offsets
        fprintf(stderr, "Invalid timezone offset. Range: -12 to +14 hours\n");
        return 1;
    }

    do {
        now = time(NULL);  // Update time in watch mode

        // Choose time base and apply timezone adjustment
        time_t adjusted_time = now;
        if (!use_local) {
            adjusted_time += (t * 3600);  // Apply timezone offset to UTC
            time_ptr = gmtime(&adjusted_time);
        } else {
            time_ptr = localtime(&now);  // Use local time as-is
        }

        // Calculate the beat value (Internet Time)
        int total_seconds_bmt =
            time_ptr->tm_hour * 3600 + time_ptr->tm_min * 60 + time_ptr->tm_sec;
        float beat = total_seconds_bmt /
                     86.4;  // 1 day = 1000 beats so 1 beat = 86.4 seconds

        if (verbose) {
            verbose_output(beat, time_ptr, t, use_local);
        } else if (show_date) {
            show_internet_date(time_ptr);
        } else {
            if (format == NULL) {
                format = "@%06.2f\n";
            }
            printf(format, beat);
        }

        if (watch_mode) {
            fflush(stdout);
            sleep(1);
        }
    } while (watch_mode);

    return 0;
}
