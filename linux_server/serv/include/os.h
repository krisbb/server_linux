#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <string.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <sys/ioctl.h>

//int os_printf(const char *format,...);
void *os_memset(void *s, int c, size_t n);
int os_socket(int domain, int type, int protocol);
int os_bind(int sockfd, const struct sockaddr *addr,
				socklen_t addrlen);
int os_listen(int sockfd, int backlog);
int os_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
void *os_malloc(size_t size);
void os_free(void *ptr);
int os_close(int fd);
int os_epoll_create(int size);
int os_epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
int os_epoll_wait(int epfd, struct epoll_event *events,
					int maxevents, int timeout);
uint32_t os_htonl(uint32_t hostlong);
uint16_t os_htons(uint16_t hostshort);
ssize_t os_read(int fd, void * buf , size_t count);
ssize_t os_write(int fd, const void * buf, size_t count);
int os_getifaddrs(struct ifaddrs **ifap);
int os_getnameinfo(const struct sockaddr *sa, socklen_t salen,
						char *host, socklen_t hostlen,
						char *serv, socklen_t servlen, int flags);
int os_ioctl(int fd, unsigned long request , void * arg);

//inet_pton ?
//memcpy ? strlen ? strcpy ? snprintf ? strcmp ? 
