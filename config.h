#pragma once

#include <errno.h>

#define MAX_FPS 60
#define FPS_LIMIT 1
#define MAX_INTERFACE_ELEMENTS 124

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define DEBUG 1

#define CHECK(condition, message, line, file) {\
    if(!(condition)) {\
        printf("%s : %d : %s\n", file, line, message);\
        return false;\
    }\
}

#define CHECK_ERROR(condition, message, detailedMessage, line, file) {\
    if(!(condition)) {\
        printf("%s : %d : %s\nDetaliat: %s\n\n", file, line, message, detailedMessage);\
        return false;\
    }\
}

struct XYPair {
    int x, y;
};