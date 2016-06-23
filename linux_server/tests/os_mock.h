extern "C" {
	#include "os.h"
}

#include <cmock/cmock.h>

DECLARE_FUNCTION_MOCK3( os_memset_mock, os_memset,void*(void*,int,size_t));
DECLARE_FUNCTION_MOCK3( os_socket_mock, os_socket,int( int, int, int));
DECLARE_FUNCTION_MOCK3( os_bind_mock, os_bind, int(int, const struct sockaddr*,socklen_t));
DECLARE_FUNCTION_MOCK2( os_listen_mock, os_listen , int(int, int));
DECLARE_FUNCTION_MOCK3( os_accept_mock, os_accept ,int(int, struct sockaddr *,socklen_t *));
DECLARE_FUNCTION_MOCK1( os_malloc_mock, os_malloc ,void *(size_t));
DECLARE_FUNCTION_MOCK1( os_free_mock, os_free ,void (void *));
DECLARE_FUNCTION_MOCK1( os_close_mock, os_close ,int(int));
DECLARE_FUNCTION_MOCK1( os_epoll_create_mock, os_epoll_create ,int(int));
DECLARE_FUNCTION_MOCK4( os_epoll_ctl_mock, os_epoll_ctl, int (int, int, int,
struct epoll_event *));
DECLARE_FUNCTION_MOCK4( os_epoll_wait_mock, os_epoll_wait,int(int,struct epoll_event *,int, int));
DECLARE_FUNCTION_MOCK1( os_htonl_mock, os_htonl, uint32_t(uint32_t));
DECLARE_FUNCTION_MOCK1( os_htons_mock, os_htons, uint16_t(uint16_t));
DECLARE_FUNCTION_MOCK3( os_read_mock, os_read, ssize_t(int, void *, size_t));
DECLARE_FUNCTION_MOCK3( os_write_mock, os_write, ssize_t (int, const void *,size_t));
DECLARE_FUNCTION_MOCK1( os_getifaddrs_mock, os_getifaddrs,int(struct ifaddrs**));
DECLARE_FUNCTION_MOCK7( os_getnameinfo_mock, os_getnameinfo,
							   int(const struct sockaddr*, socklen_t,
							   char *, socklen_t, char *, socklen_t, int));
DECLARE_FUNCTION_MOCK3( os_ioctl_mock, os_ioctl, int(int, unsigned long, void*));

