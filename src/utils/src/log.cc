#include <utils/log.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void ulog(msg_type type, const char* format, ...) {
#define COLOR_NONE "\033[0m"
#define RED        "\033[1;31;40m"
#define BLUE       "\033[1;34;40m"
#define GREEN      "\033[1;32;40m"
#define YELLOW     "\033[1;33;40m"

    char* msg_content = NULL;
    va_list arg_list_raw;
    va_start(arg_list_raw, format);
    va_list arg_list;
    va_copy(arg_list, arg_list_raw);

    // 计算所需的内存空间大小
    int len = vsnprintf(NULL, 0, format, arg_list);
    if (len < 0) {
        // 出错处理
        return;
    }

    // 分配内存空间
    msg_content = (char*)malloc(len + 1);
    if (msg_content == NULL) {
        // 内存分配失败处理
        return;
    }

    // 使用 vsprintf 填充 msg_content
    va_copy(arg_list, arg_list_raw);
    vsnprintf(msg_content, len + 1, format, arg_list);

    va_end(arg_list_raw);
    va_end(arg_list);

    switch(type) {
        case MSG_INFO:
            printf(GREEN "[INFO] %s\n" COLOR_NONE, msg_content);
            break;
        case MSG_DEBUG:
            printf(BLUE "[DEBUG]: %s\n" COLOR_NONE, msg_content);
            break;
        case MSG_WARN:
            printf(YELLOW "[WARN]: %s\n" COLOR_NONE, msg_content);
            break;
        case MSG_ERROR:
            printf(RED "[ERROR]: %s\n" COLOR_NONE, msg_content);
            break;               
        default:                 
            printf("[ERROR_LOG]: %s\n", msg_content);
    }

    // 释放内存
    free(msg_content);

#undef COLOR_NONE
#undef RED       
#undef BLUE      
#undef GREEN     
#undef YELLOW    
}
