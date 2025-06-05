#include <stdio.h>
#include "BlockSpwan.h"
#include "PanData.h"

static int test_blockspwan(void) {
    for (int i = 0; i < 100; ++i) {
        int val = BlockSpwan();
        if (val < 0 || val > 6) {
            printf("BlockSpwan returned out of range value %d\n", val);
            return 1;
        }
    }
    return 0;
}

static int test_panmap(void) {
    int map[22][12] = {0};
    PanMap(map);
    for (int i = 0; i < 12; ++i) {
        if (map[0][i] != 2 || map[21][i] != 2) {
            printf("PanMap failed at top/bottom border\n");
            return 1;
        }
    }
    for (int i = 0; i < 22; ++i) {
        if (map[i][0] != 2 || map[i][11] != 2) {
            printf("PanMap failed at left/right border\n");
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int result = 0;
    result |= test_blockspwan();
    result |= test_panmap();
    if (result == 0) {
        printf("All tests passed\n");
    }
    return result;
}

