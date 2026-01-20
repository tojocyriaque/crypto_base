#ifndef __UINT256__
#define __UINT256__

#include <cstdint>

using namespace std;

// 256bits integer composed of 4 64bits blocks
typedef struct {
    uint64_t blocks[4];
} uint256_t;

#endif
