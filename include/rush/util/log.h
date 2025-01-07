#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define LOG_FILE_PATH "/var/log/rush.log"

typedef struct str_builder str_builder;

struct str_builder {
    char *content;
    size_t capacity;
    size_t len;
};

str_builder *str_builder_init(void);

void str_builder_destroy(str_builder *b);

void str_builder_add_char(str_builder *b, char c);

void str_builder_add_str(str_builder *b, char *s, size_t l);

void str_builder_add_int(str_builder *b, int i);

void str_builder_add_double(str_builder *b, double v);

char *str_builder_get(str_builder *b);

typedef struct {
    int type;
    const char *frmt;
    struct tm *time;
} log_event;

typedef struct log_queue_node log_queue_node;

struct log_queue_node {
    log_event *evt;
    log_queue_node *next;
};

typedef struct {
    log_queue_node *front;
    log_queue_node *rear;
    int size;
} log_queue;

log_queue log_queue_init();

bool is_log_queue_empty(log_queue *q);

int log_queue_size(log_queue *q);

log_event *log_queue_peek(log_queue *q);

void log_enqueue(log_queue *q, log_event evt);

log_event *log_dequeue(log_queue *q);

enum { DEBUG, INFO, WARN, FATAL };

#define log_debug(...) call_log_event(DEBUG, __VA_ARGS__)
#define log_info(...) call_log_event(INFO, __VA_ARGS__)
#define log_warn(...) call_log_event(WARN, __VA_ARGS__)
#define log_fatal(...) call_log_event(FATAL, __VA_ARGS__)

void call_log_event(int type, char *frmt, ...);

#endif