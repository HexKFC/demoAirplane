#include <utils/log.h>
#include <stdio.h>
#include <stdarg.h>

void OutputLog(msg_type type, const char* format, ...) {
    char* msg_content;
    va_list arg_list;
    vsprintf(msg_content, format, arg_list);
    switch(type) {
        case msg_info:
            printf("[INFO] %s\n", msg_content);
            break;
        case msg_debug:
            printf("[DEBUG]: %s\n", msg_content);
            break;
        case msg_warn:
            printf("[WARN]: %s\n", msg_content);
            break;
        case msg_error:
            printf("[ERROR]: %s\n", msg_content);
            break;               
        default:                 
            printf("[ERROR_LOG]: %s\n", msg_content);
    }
}
