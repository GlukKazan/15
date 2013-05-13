#include "initializer.h"

Task Initializer::tasks[MAX_TASKS];
int  Initializer::digits[MAX_DIGIT + 1];

bool Initializer::solve() {
    if (!init(startPos, endPos)) return false;
    while (true) {
        int mn = stepCnt;
        int ix = -1;
        for (int i = 0; i < taskCnt; i++) {
            if (tasks[i].isProcessed) continue;
            if (stepCnt - tasks[i].delta < mn) {
                mn = stepCnt - tasks[i].delta;
                ix = i;
            }
        }
        if (ix < 0) break;
        tasks[ix].isProcessed = true;
        Solver solver(tasks[ix].startPos, tasks[ix].endPos, stepCnt);
        if (solver.solve()) return true;
    }
    return false;
}

bool Initializer::checkInit(Long s, Long e) {
    for (int i = 0; i <= MAX_DIGIT; i++) {
         digits[i] = 0;
    }
    for (int i = 0; i <= MAX_DIGIT; i++) {
        digits[s & 0xF]++;
        s >>= 4;
    }
    if (digits[0] != 1) return false;
    for (int i = 0; i <= MAX_DIGIT; i++) {
        digits[e & 0xF]--;
        e >>= 4;
    }
    for (int i = 0; i <= MAX_DIGIT; i++) {
         if (digits[i] != 0) return false;
    }
    return true;
}

bool Initializer::addPos(Long s, Long e) {
    if (!checkPos(s, e)) return true;
    if (taskCnt >= MAX_TASKS) return false;
    tasks[taskCnt].startPos = s;
    tasks[taskCnt].endPos = e;
    tasks[taskCnt].delta = getDelta(s, e);
    tasks[taskCnt].isProcessed = false;
    if (tasks[taskCnt].delta == 0) return false;
    if (tasks[taskCnt].delta > stepCnt) return true;
    taskCnt++;
    return true;
}

Long Initializer::getFreeDigit() {
    for (Long i = 1; i <= MAX_DIGIT; i++) {
        if (digits[i] == 0) return i;
    }
    return 0;
}

bool Initializer::init(Long s, Long e) {
    for (int i = 0; i <= MAX_DIGIT; i++) {
         digits[i] = 0;
    }
    Long x = s;
    for (int i = 0; i <= MAX_DIGIT; i++) {
        digits[x & 0xF]++;
        x >>= 4;
    }
    bool f = true;
    for (int i = 0; i <= MAX_DIGIT; i++) {
         if (digits[i] != 1) f = false;
    }
    if (f) {
        return addPos(s, e);
    }
    Long d = getFreeDigit();
    if (d == 0) return false;
    x = s;
    Long ms = 0xF;
    for (int i = 0; i <= MAX_DIGIT; i++) {
        Long t = x & 0xF;
        if (digits[t] > 1) {
            setDigit(s, ms, d);
            Long y = e;
            Long me = 0xF;
            for (int j = 0; j <= MAX_DIGIT; j++) {
                if ((y & me) == t) {
                    Long k = e;
                    setDigit(k, me, d);
                    if (!init(s, k)) return false;
                }
                me <<= 4;
                y >>= 4;
            }
            break;
        }
        ms <<= 4;
        x >>= 4;
    }
    return true;
}

void Initializer::normalize(Long& p) {
    int x = getX(p);
    int y = getY(p);
    for (; x < 4; x++) {
        Long d = getDigit(p, x + 1, y);
        xorDigit(p, x + 1, y, d);
        xorDigit(p, x, y, d);
    }
    for (; y < 4; y++) {
        Long d = getDigit(p, x, y + 1);
        xorDigit(p, x, y + 1, d);
        xorDigit(p, x, y, d);
    }
}

bool Initializer::checkPos(Long s, Long e) {
    normalize(s); normalize(e);
    Long nums[16] = {0};
    int  ix = 0;
    for (int y = 1; y < 4; y++) {
        for (int x = 1; x < 4; x++) {
            Long d = getDigit(e, x, y);
            if (d != 0) {
                nums[d] = ++ix;
            }
        }
    }
    int cn = 0;
    for (int y = 1; y < 4; y++) {
        for (int x = 1; x < 4; x++) {
            Long d = getDigit(s, x, y);
            for (Long i = 1; i <= 15; i++) {
                if (nums[i] < nums[d]) {
                    int Y = getY(s, i);
                    if (Y < y) continue;
                    if (Y > y) {
                        cn++;
                        break;
                    }
                    int X = getX(s, i);
                    if (X > x) {
                        cn++;
                        break;
                    }
                }
            }
        }
    }
    return (cn & 1) == 0;
}
