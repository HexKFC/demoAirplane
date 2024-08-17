#ifndef CRASH_CHECK_H
#define CRASH_CHECK_H
#include <SDL_rect.h>

// true -> crash
// false-> not crash
bool CrashCheck(SDL_Rect* obj1, SDL_Rect* obj2);

#endif // CRASH_CHECK_H
