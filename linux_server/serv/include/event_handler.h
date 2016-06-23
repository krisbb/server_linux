#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <stdint.h> //przenosnosc dlugosc uint32_t

typedef struct reactor reactor;

typedef struct event_handler {
	int fd;
	reactor *r;
	void (*handle_event)(struct event_handler* self, uint32_t event);
} event_handler;

#endif
