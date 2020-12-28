#pragma once

#define MAX_FPS 144
#define FPS_LIMIT 1
#define MAX_INTERFACE_ELEMENTS 124

#define KEYS_NUMBER 1024

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define DEBUG 1



#define CHECK(condition, message, line, file) {\
    if(!(condition)) {\
        printf("ERROR - file: %s la linia %d:\n%s\n\n", file, line, message);\
        return false;\
    }\
}

#define CHECK_ERROR(condition, message, detailedMessage, line, file) {\
    if(!(condition)) {\
        printf("ERROR: - file: %s la linia %d:\n%s\nDetaliat: %s\n\n", file, line, message, detailedMessage);\
        return false;\
    }\
}

struct XYPair {
    int x, y;
};