#ifndef LOG_H
#define LOG_H
typedef enum {
    MSG_INFO,
    MSG_DEBUG,
    MSG_WARN,
    MSG_ERROR
} msg_type;

void ulog(msg_type type, const char* format, ...);
#endif // !LOG_H
