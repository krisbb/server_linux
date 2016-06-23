#include "event_handler.h"
#include <stddef.h>

typedef struct reactor_core {
	int epoll_sock;
	size_t current_idx;
	event_handler** ehq;
} reactor_core;

typedef struct reactor {
	void (*add_event_handler)(reactor* self, event_handler* eh);
	void (*remove_event_handler)(reactor* self, int fd);
	void (*event_loop)(reactor* self);
	int MaxClients;
	reactor_core*rc;
} reactor;

reactor* create_reactor(int epoll_sock, int MaxClients);
void destroy_reactor(reactor* r);


