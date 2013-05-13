#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#include "common.h"
#include "solver.h"

struct Task {
    Long startPos;
    Long endPos;
    int  delta;
    bool isProcessed;
};

class Initializer {
    public:
        Initializer(Long startPos, Long endPos, int stepCnt): startPos(startPos), endPos(endPos), stepCnt(stepCnt), taskCnt(0) {}
        bool solve();
    private:
        Long        startPos;
        Long        endPos;
        int         stepCnt;
        int         taskCnt;
        static Task tasks[MAX_TASKS];
        static int  digits[MAX_DIGIT + 1];
        bool checkInit(Long s, Long e);
        bool addPos(Long s, Long e);
        bool init(Long s, Long e);
        Long getFreeDigit();
        bool checkPos(Long s, Long e);
        void normalize(Long& p);
};

#endif