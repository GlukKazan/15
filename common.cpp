#include "common.h"
#include <math.h>

Long digit[MAX_DIGIT + 1] = {
    0x0000000000000000L,
    0x1111111111111111L,
    0x2222222222222222L,
    0x3333333333333333L,
    0x4444444444444444L,
    0x5555555555555555L,
    0x6666666666666666L,
    0x7777777777777777L,
    0x8888888888888888L,
    0x9999999999999999L,
    0xAAAAAAAAAAAAAAAAL,
    0xBBBBBBBBBBBBBBBBL,
    0xCCCCCCCCCCCCCCCCL,
    0xDDDDDDDDDDDDDDDDL,
    0xEEEEEEEEEEEEEEEEL,
    0xFFFFFFFFFFFFFFFFL 
};

int getPosition(Long part) {
    for (int i = 4; i > 0; i--) {
        if ((part & 0xF) == 0) return i;
        part >>= 4;
    }
    return 0;
}

int getX(Long state) {
    for (int i = 4; i >= 1; i--) {
        int r = getPosition(state & 0xFFFF);
        if (r != 0) return r;
        state >>= 16;
    }
    return 0;
}

int getY(Long state) {
    for (int i = 4; i >= 1; i--) {
        int r = getPosition(state & 0xFFFF);
        if (r != 0) return i;
        state >>= 16;
    }
    return 0;
}

int getX(Long state, Long d) {
    state ^= digit[d];
    return getX(state);
}

int getY(Long state, Long d) {
    state ^= digit[d];
    return getY(state);
}

int getDeltaX(Long a, Long b, Long d) {
    a ^= digit[d]; b ^= digit[d];
    return getX(a) - getX(b);
}

int getDeltaY(Long a, Long b, Long d) {
    a ^= digit[d]; b ^= digit[d];
    return getY(a) - getY(b);
}

int getDelta(Long a, Long b) {
    int r = 0;
    for (Long d = 1; d <= MAX_DIGIT; d++) {
        r += abs(getDeltaX(a, b, d));
        r += abs(getDeltaY(a, b, d));
    }
    return r;
}

Long getDigit(Long p, int x, int y) {
    for (; y <= 4; y++) {
        if (y == 4) {
            p &= 0xFFFF;
            for (; x <= 4; x++) {
                if (x == 4) {
                    return p & 0xF;
                }
                p >>= 4;
            }
            break;
        }
        p >>= 16;
    }
    return -1;
}

void xorDigit(Long& p, int x, int y, Long d) {
    for (; x < 4; x++) {
        d <<= 4;
    }
    for (; y < 4; y++) {
        d <<= 16;
    }
    p ^= d;
}

void setDigit(Long& p, Long m, Long d) {
    p ^= p & m;
    m &= digit[d];
    p ^= m;
}
