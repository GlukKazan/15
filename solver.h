#ifndef SOLVER_H_
#define SOLVER_H_

#include <stdio.h>
#include "common.h"
#include "PerfCnt.h"

class Solver {
    public:
        Solver(Long startPos, Long endPos, int stepCnt): startPos(startPos), endPos(endPos), stepCnt(stepCnt), posCnt(0), perfCnt() {}
        bool solve();
    private:
        Long        startPos;
        Long        endPos;
        int         stepCnt;
        Long        posCnt;
        PerfCnt     perfCnt;
        static Long pos[MAX_DEEP];
        static Byte step[MAX_DEEP];
        void dumpSolve(int deep);
        void dumpPos(int delta);
        void dumpTotal();
        bool checkPos(Long p, int deep);
        bool solve(int deep, int delta, int startDelta, int X, int Y);
        Long getStep(Long p, int x, int y, int dx, int dy, int& dd);
};

#endif
