#ifndef COMMON_H_
#define COMMON_H_

typedef unsigned __int64 Long;
typedef unsigned __int16 Short;
typedef unsigned char    Byte;

const int MAX_POSITION    = 4;
const int MAX_DIGIT       = 15;
const int MAX_DEEP        = 100;
const int MAX_LOOP        = 10;
const int MAX_TASKS       = 100;
const int MAX_DELTA_DIFF  = 5;

int  getPosition(Long part);
int  getX(Long state);
int  getY(Long state);
int  getX(Long state, Long d);
int  getY(Long state, Long d);
int  getDeltaX(Long a, Long b, Long d);
int  getDeltaY(Long a, Long b, Long d);
int  getDelta(Long a, Long b);
Long getDigit(Long p, int x, int y);
void xorDigit(Long& p, int x, int y, Long d);
void setDigit(Long& p, Long m, Long d);

#endif
