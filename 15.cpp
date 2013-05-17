#include <iostream>
#include <tchar.h>
#include "initializer.h"

int _tmain(int argc, _TCHAR* argv[])
{
    Initializer m(0x513492B7D6A80EFC, 0x123456789ABCDEF0, 12);
    m.solve();
    return 0;
}

