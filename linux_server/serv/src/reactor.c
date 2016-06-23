//implementation of reactor design pattern
#include <sys/epoll.h>
#include <unistd.h>
#include "reactor.h"
#include "os.h"

//
//#define MAX_USERS 1
//trzeba cos wykombinowac z MAX_USERS bo to zalezy od naszego configa
//#define MAX_IDX    //(MAX_USERS-1)


static event_handler* find_eh(reactor_core* rc, int fd, size_t* idx)//
{
	size_t i = 0;
	event_handler* eh = NULL;
	for( i = 0; i <= rc->current_idx; i++) {
		if (rc->ehq[i] && (rc->ehq[i]->fd == fd)) {
			eh = rc->ehq[i];
			if (idx)
				*idx = i;
			break;
		}
	}
	return eh;
}

static void add_event_handler(reactor* self, event_handler* eh)//
{
	struct epoll_event ee;
	os_memset(&ee, 0, sizeof(ee));
	ee.events = EPOLLIN;
	ee.data.fd = eh->fd;
	
	// if fail return -1 
	os_epoll_ctl(self->rc->epoll_sock, EPOLL_CTL_ADD, eh->fd, &ee);

	if(self->rc->current_idx < (self->MaxClients + 1 ) ) {
		if ((self->rc->current_idx == 0) && (self->rc->ehq[0] == 0))
			self->rc->ehq[0] = eh;
		else
			self->rc->ehq[++(self->rc->current_idx)] = eh;
	}
}

static void remove_event_handler(reactor* self, int fd)//
{
	size_t i = 0;
	event_handler* eh = find_eh(self->rc, fd, &i);
	if(!eh)
		return;

	if (i < self->rc->current_idx)
		self->rc->ehq[i] = self->rc->ehq[self->rc->current_idx];

	self->rc->ehq[self->rc->current_idx] = 0;
	if (self->rc->current_idx > 0 )
	   --self->rc->current_idx;

	os_epoll_ctl(self->rc->epoll_sock, EPOLL_CTL_DEL, eh->fd, 0);
	os_close(eh->fd);
	os_free(eh);
}

static void event_loop(reactor* self)
{
	int i = 0;
	int epoll_sock = self->rc->epoll_sock;
	struct epoll_event es[self->MaxClients];
	event_handler* eh = 0;

	for(;;){

		i = os_epoll_wait(epoll_sock, es, self->MaxClients , -1);

		if ( i < 0 )
		{
			printf("epoll wait failed\n");
			break;
		}

		for (--i; i > -1; --i) {
			eh = find_eh(self->rc, es[i].data.fd, 0);
			if(eh)
				eh->handle_event(eh, es[i].events);
		}
	}
}

reactor* create_reactor(int epoll_sock, int MaxClients )//
{
	reactor * r = os_malloc(sizeof(reactor));

	if( r == NULL )
		return NULL;

	r->rc = os_malloc(sizeof(reactor_core));

	if( r->rc == NULL )
	{
		os_free(r);
		return NULL;
	}

	r->rc->ehq = os_malloc(sizeof(event_handler)*( MaxClients + 1 ));

	if( r->rc->ehq == NULL )
	{
		os_free(r->rc);
		os_free(r);
		return NULL;
	}

	r->rc->ehq[0] = 0;
	r->rc->epoll_sock = epoll_sock;
	r->rc->current_idx = 0;
	
	r->MaxClients = MaxClients;
	r->add_event_handler = &add_event_handler;
	r->remove_event_handler = &remove_event_handler;
	r->event_loop = &event_loop;
	
	return r;
}

void destroy_reactor(reactor* r)//
{
	os_free(r->rc->ehq);
	os_free(r->rc);
	os_free(r);
}
