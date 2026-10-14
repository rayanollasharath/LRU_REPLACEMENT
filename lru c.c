/* LRU PAGE REPLACEMENT ALGORITHM - OSSP PBL (C IMPLEMENTATION) */
#include <stdio.h>

#define MAX 50

/* RETURNS THE INDEX OF THE LEAST RECENTLY USED FRAME */
int findLRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;
    int frame[MAX], time[MAX];
    int counter = 0, faults = 0, hits = 0, filled = 0;
    int i, j, found, pos;

    printf("LRU PAGE REPLACEMENT ALGORITHM\n");
    printf("NUMBER OF PAGES  : %d\n", n);
    printf("NUMBER OF FRAMES : %d\n\n", frames);
    printf("%-6s%-18s%s\n", "PAGE", "FRAMES", "STATUS");
    printf("----------------------------------\n");

    for (i = 0; i < n; i++) {
        found = 0;
        counter++;

        /* CHECK FOR A PAGE HIT */
        for (j = 0; j < filled; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                time[j] = counter;      /* UPDATE LAST USED TIME */
                hits++;
                break;
            }
        }

        /* PAGE FAULT */
        if (!found) {
            faults++;
            if (filled < frames) {      /* FREE FRAME AVAILABLE */
                frame[filled] = pages[i];
                time[filled] = counter;
                filled++;
            } else {                    /* REPLACE LRU PAGE */
                pos = findLRU(time, frames);
                frame[pos] = pages[i];
                time[pos] = counter;
            }
        }

        printf("%-6d", pages[i]);
        for (j = 0; j < frames; j++) {
            if (j < filled) printf("%-3d", frame[j]);
            else            printf("%-3s", "-");
        }
        printf("%*s%s\n", 18 - 3 * frames, "", found ? "HIT" : "FAULT");
    }

    printf("----------------------------------\n");
    printf("TOTAL REFERENCES : %d\n", n);
    printf("PAGE FAULTS      : %d\n", faults);
    printf("PAGE HITS        : %d\n", hits);
    printf("HIT RATIO        : %.2f\n", (float)hits / n);
    printf("FAULT RATIO      : %.2f\n", (float)faults / n);
    return 0;
}
