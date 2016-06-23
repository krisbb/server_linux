// os.c implementacje funkcji systemowych owrapowane na potrzeby testowania
#include "os.h"

//int os_printf(const char *format,...);
void *os_memset(void *s, int c, size_t n)
{
	return memset(s, c, n);
}

int os_socket(int domain, int type, int protocol)
{
	return socket(domain, type, protocol);
}

int os_bind(int sockfd, const struct sockaddr *addr,
				socklen_t addrlen)
{
	return bind(sockfd, addr, addrlen);
}

int os_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	return accept(sockfd , addr , addrlen);
}

int os_listen(int sockfd, int backlog)
{
	return listen(sockfd, backlog);
}

void *os_malloc(size_t size)
{
	return malloc(size);
}

void os_free(void *ptr)
{
	return free(ptr);
}

int os_close(int fd)
{
	return close(fd);
}

int os_epoll_create(int size)
{
	return epoll_create(size);
}

int os_epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
{
	return epoll_ctl(epfd, op, fd, event);
}

int os_epoll_wait(int epfd, struct epoll_event *events,
					int maxevents, int timeout)
{
	return epoll_wait(epfd, events, maxevents, timeout);
}

uint32_t os_htonl(uint32_t hostlong)
{
	return htonl(hostlong);
}

uint16_t os_htons(uint16_t hostshort)
{
	return htons(hostshort);
}

ssize_t os_read(int fd, void * buf , size_t count)
{
	return read(fd ,buf ,count);
}

ssize_t os_write(int fd, const void * buf, size_t count)
{
	return write(fd,buf,count);
}

int os_getifaddrs(struct ifaddrs **ifap)
{
	return getifaddrs(ifap);
}

int os_getnameinfo(const struct sockaddr *sa, socklen_t salen,
						char *host, socklen_t hostlen,
						char *serv, socklen_t servlen, int flags)
{
	return getnameinfo(sa ,salen, host , hostlen,
							 serv, servlen , flags);
}

int os_ioctl(int d, unsigned long request , void * arg)
{
	return ioctl(d,request,arg);
}

