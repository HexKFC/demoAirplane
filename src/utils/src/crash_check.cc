#include <SDL_rect.h>
#include <utils/crash_check.h>

bool CrashCheck(SDL_Rect* obj1, SDL_Rect* obj2) {
    return (obj2->x > obj1->x - obj2->w && 
            obj2->x < obj1->x + obj1->w &&
            obj2->y > obj1->y - obj2->h &&
            obj2->y < obj1->y + obj1->h);
}
