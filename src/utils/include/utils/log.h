#ifndef LOG_H
#define LOG_H
typedef enum {
    msg_info,
    msg_debug,
    msg_warn,
    msg_error
} msg_type;

void OutputLog(msg_type type, const char* format, ...);
#endif // !LOG_H
