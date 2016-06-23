extern "C" {
 #include "s_prep.h"
 #include "s_config.h"
 #include "reactor.h"
 #include "acceptor.h"
 #include "server.h"
}

#include "os_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

ACTION_P(r_size, size)
{
	memcpy(arg1, size ,strlen(size));
	return strlen(size);
};

ACTION_P(r_msg, msg)
{
	memcpy(arg1, msg ,strlen(msg));
	return strlen(msg);
};


/*	Good accept client no event
TEST( server_test , handle_message_av_interfaces)
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;
	os_epoll_wait_mock ewm;
	os_accept_mock acm;

	int serv_fd = 1;
	int epoll_sock = 2; 
	int client_fd = 3;

	struct epoll_event e;
	e.events = EPOLLIN;
	e.data.fd = serv_fd;

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,_)).WillOnce(Return(0));

	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,_,_)).Times(3).WillRepeatedly(Return(0));
	EXPECT_FUNCTION_CALL(ewm, (epoll_sock,_,_,-1)).Times(2).WillOnce(DoAll(SetArgPointee<1>(e), Return(1))).WillOnce(Return(-1));

	EXPECT_FUNCTION_CALL(acm , (serv_fd , _,_)).WillOnce(Return(client_fd));

	

	server(1,NULL);

	ASSERT_TRUE(true);
}
*/
TEST( server_test , foo_av_interfaces)
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;
	os_epoll_wait_mock ewm;
	os_accept_mock acm;
	os_read_mock rm;

	int serv_fd = 1;
	int epoll_sock = 2; 
	int client_fd = 3;

	struct epoll_event e;
	e.events = EPOLLIN;
	e.data.fd = serv_fd;

	struct epoll_event ec;
	ec.events = EPOLLIN;
	ec.data.fd = client_fd;

	const char * rlen  = "0.0.5";
	const char * rmsg = "1.0.2";

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,_)).WillOnce(Return(0));

	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,_,_)).Times(3).WillRepeatedly(Return(0));
	EXPECT_FUNCTION_CALL(ewm, (epoll_sock,_,_,-1)).Times(3).\
	WillOnce(DoAll(SetArgPointee<1>(e), Return(1))).\
	WillOnce(DoAll(SetArgPointee<1>(ec), Return(1))).\
	WillOnce(Return(-1));

	EXPECT_FUNCTION_CALL(acm , (serv_fd , _,_)).WillOnce(Return(client_fd));
	EXPECT_FUNCTION_CALL(rm , (client_fd , _ , _ )).\
	WillOnce(r_size(rlen)).WillOnce(r_msg(rmsg));
	
	server(1,NULL);

	ASSERT_TRUE(true);
}

TEST( server_test , foo_test)
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;
	os_epoll_wait_mock ewm;
	os_accept_mock acm;
	os_read_mock rm;

	int serv_fd = 1;
	int epoll_sock = 2; 
	int client_fd = 3;

	struct epoll_event e;
	e.events = EPOLLIN;
	e.data.fd = serv_fd;

	struct epoll_event ec;
	ec.events = EPOLLIN;
	ec.data.fd = client_fd;

	const char * rlen  = "0.0.5";
	const char * rmsg = "1.0.1";

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,_)).WillOnce(Return(0));

	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,_,_)).Times(3).WillRepeatedly(Return(0));
	EXPECT_FUNCTION_CALL(ewm, (epoll_sock,_,_,-1)).Times(3).\
	WillOnce(DoAll(SetArgPointee<1>(e), Return(1))).\
	WillOnce(DoAll(SetArgPointee<1>(ec), Return(1))).\
	WillOnce(Return(-1));

	EXPECT_FUNCTION_CALL(acm , (serv_fd , _,_)).WillOnce(Return(client_fd));
	EXPECT_FUNCTION_CALL(rm , (client_fd , _ , _ )).\
	WillOnce(r_size(rlen)).WillOnce(r_msg(rmsg));
	
	server(1,NULL);

	ASSERT_TRUE(true);
}

TEST( server_test , foo_all_interfaces)
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;
	os_epoll_wait_mock ewm;
	os_accept_mock acm;
	os_read_mock rm;

	int serv_fd = 1;
	int epoll_sock = 2; 
	int client_fd = 3;

	struct epoll_event e;
	e.events = EPOLLIN;
	e.data.fd = serv_fd;

	struct epoll_event ec;
	ec.events = EPOLLIN;
	ec.data.fd = client_fd;

	const char * rlen  = "0.0.5";
	const char * rmsg = "1.0.3";

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,_)).WillOnce(Return(0));

	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,_,_)).Times(3).WillRepeatedly(Return(0));
	EXPECT_FUNCTION_CALL(ewm, (epoll_sock,_,_,-1)).Times(3).\
	WillOnce(DoAll(SetArgPointee<1>(e), Return(1))).\
	WillOnce(DoAll(SetArgPointee<1>(ec), Return(1))).\
	WillOnce(Return(-1));

	EXPECT_FUNCTION_CALL(acm , (serv_fd , _,_)).WillOnce(Return(client_fd));
	EXPECT_FUNCTION_CALL(rm , (client_fd , _ , _ )).\
	WillOnce(r_size(rlen)).WillOnce(r_msg(rmsg));
	
	server(1,NULL);

	ASSERT_TRUE(true);
}

TEST( server_test , foo_interface_ok)
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;
	os_epoll_wait_mock ewm;
	os_accept_mock acm;
	os_read_mock rm;

	int serv_fd = 1;
	int epoll_sock = 2; 
	int client_fd = 3;

	struct epoll_event e;
	e.events = EPOLLIN;
	e.data.fd = serv_fd;

	struct epoll_event ec;
	ec.events = EPOLLIN;
	ec.data.fd = client_fd;

	const char * rlen  = "0.0.11";
	const char * rmsg = "1.0.4;lo;31";

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,_)).WillOnce(Return(0));

	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,_,_)).Times(3).WillRepeatedly(Return(0));
	EXPECT_FUNCTION_CALL(ewm, (epoll_sock,_,_,-1)).Times(3).\
	WillOnce(DoAll(SetArgPointee<1>(e), Return(1))).\
	WillOnce(DoAll(SetArgPointee<1>(ec), Return(1))).\
	WillOnce(Return(-1));

	EXPECT_FUNCTION_CALL(acm , (serv_fd , _,_)).WillOnce(Return(client_fd));
	EXPECT_FUNCTION_CALL(rm , (client_fd , _ , _ )).\
	WillOnce(r_size(rlen)).WillOnce(r_msg(rmsg));
	
	server(1,NULL);

	ASSERT_TRUE(true);
}

TEST( server_test , foo_set_mac_ok)
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;
	os_epoll_wait_mock ewm;
	os_accept_mock acm;
	os_read_mock rm;
	os_ioctl_mock ioctlm;

	int serv_fd = 1;
	int epoll_sock = 2; 
	int client_fd = 3;
	int ioctl_fd = 4;

	struct epoll_event e;
	e.events = EPOLLIN;
	e.data.fd = serv_fd;

	struct epoll_event ec;
	ec.events = EPOLLIN;
	ec.data.fd = client_fd;

	const char * rlen  = "0.0.27";
	const char * rmsg = "1.0.5;lo;00:00:00:00:00:00;";

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).Times(2).WillOnce(Return(serv_fd)).\
	WillOnce(Return(ioctl_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,_)).WillOnce(Return(0));

	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,_,_)).Times(3).WillRepeatedly(Return(0));
	EXPECT_FUNCTION_CALL(ewm, (epoll_sock,_,_,-1)).Times(3).\
	WillOnce(DoAll(SetArgPointee<1>(e), Return(1))).\
	WillOnce(DoAll(SetArgPointee<1>(ec), Return(1))).\
	WillOnce(Return(-1));

	EXPECT_FUNCTION_CALL(acm , (serv_fd , _,_)).WillOnce(Return(client_fd));
	EXPECT_FUNCTION_CALL(rm , (client_fd , _ , _ )).\
	WillOnce(r_size(rlen)).WillOnce(r_msg(rmsg));

	EXPECT_FUNCTION_CALL(ioctlm ,(ioctl_fd,_,_)).WillOnce(Return(0));
		
	server(1,NULL);

	ASSERT_TRUE(true);
}

TEST( server_test , foo_set_ip_netmask_ok)
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;
	os_epoll_wait_mock ewm;
	os_accept_mock acm;
	os_read_mock rm;
	os_ioctl_mock ioctlm;

	int serv_fd = 1;
	int epoll_sock = 2; 
	int client_fd = 3;
	int ioctl_fd = 4;

	struct epoll_event e;
	e.events = EPOLLIN;
	e.data.fd = serv_fd;

	struct epoll_event ec;
	ec.events = EPOLLIN;
	ec.data.fd = client_fd;

	const char * rlen  = "0.0.32";
	const char * rmsg = "1.0.6;lo;127.0.0.1;255.255.255.0";

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).Times(2).WillOnce(Return(serv_fd)).\
	WillOnce(Return(ioctl_fd));

	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,_)).WillOnce(Return(0));

	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,_,_)).Times(3).WillRepeatedly(Return(0));
	EXPECT_FUNCTION_CALL(ewm, (epoll_sock,_,_,-1)).Times(3).\
	WillOnce(DoAll(SetArgPointee<1>(e), Return(1))).\
	WillOnce(DoAll(SetArgPointee<1>(ec), Return(1))).\
	WillOnce(Return(-1));

	EXPECT_FUNCTION_CALL(acm , (serv_fd , _,_)).WillOnce(Return(client_fd));
	EXPECT_FUNCTION_CALL(rm , (client_fd , _ , _ )).\
	WillOnce(r_size(rlen)).WillOnce(r_msg(rmsg));

	EXPECT_FUNCTION_CALL(ioctlm ,(ioctl_fd,_,_)).Times(2).WillRepeatedly(Return(0));
	
	server(1,NULL);

	ASSERT_TRUE(true);
}

TEST( server_test , foo_remove_client)
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;
	os_epoll_wait_mock ewm;
	os_accept_mock acm;
	os_read_mock rm;

	int serv_fd = 1;
	int epoll_sock = 2; 
	int client_fd = 3;

	struct epoll_event e;
	e.events = EPOLLIN;
	e.data.fd = serv_fd;

	struct epoll_event ec;
	ec.events = EPOLLIN;
	ec.data.fd = client_fd;

	const char * rlen  = "0.0.5";
	const char * rmsg = "1.0.9";

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,_)).WillOnce(Return(0));

	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,_,_)).Times(4).WillRepeatedly(Return(0));
	EXPECT_FUNCTION_CALL(ewm, (epoll_sock,_,_,-1)).Times(3).\
	WillOnce(DoAll(SetArgPointee<1>(e), Return(1))).\
	WillOnce(DoAll(SetArgPointee<1>(ec), Return(1))).\
	WillOnce(Return(-1));

	EXPECT_FUNCTION_CALL(acm , (serv_fd , _,_)).WillOnce(Return(client_fd));
	EXPECT_FUNCTION_CALL(rm , (client_fd , _ , _ )).\
	WillOnce(r_size(rlen)).WillOnce(r_msg(rmsg));
	
	server(1,NULL);

	ASSERT_TRUE(true);
}

TEST( server_test , foo_wrong_protocol)
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;
	os_epoll_wait_mock ewm;
	os_accept_mock acm;
	os_read_mock rm;

	int serv_fd = 1;
	int epoll_sock = 2; 
	int client_fd = 3;

	struct epoll_event e;
	e.events = EPOLLIN;
	e.data.fd = serv_fd;

	struct epoll_event ec;
	ec.events = EPOLLIN;
	ec.data.fd = client_fd;

	const char * rlen  = "0.0.5";
	const char * rmsg = "1.0.A";

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,_)).WillOnce(Return(0));

	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,_,_)).Times(3).WillRepeatedly(Return(0));
	EXPECT_FUNCTION_CALL(ewm, (epoll_sock,_,_,-1)).Times(3).\
	WillOnce(DoAll(SetArgPointee<1>(e), Return(1))).\
	WillOnce(DoAll(SetArgPointee<1>(ec), Return(1))).\
	WillOnce(Return(-1));

	EXPECT_FUNCTION_CALL(acm , (serv_fd , _,_)).WillOnce(Return(client_fd));
	EXPECT_FUNCTION_CALL(rm , (client_fd , _ , _ )).\
	WillOnce(r_size(rlen)).WillOnce(r_msg(rmsg));
	
	server(1,NULL);

	ASSERT_TRUE(true);
}





TEST( server_test , socket_failure)
{
	os_socket_mock sm;

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(-1));

	server(1,NULL);

	ASSERT_TRUE(true);
}
/*
TEST( server_test , bind_failure)
{
	os_socket_mock sm;
	os_bind_mock bm;

	int s_fd = 1;
	
	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(s_fd));
	EXPECT_FUNCTION_CALL(bm, (s_fd,_,_)).WillOnce(Return(-1));

	server(1,NULL);
	
	ASSERT_TRUE(true);
}


TEST( server_test , listen_failure)
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;

	int serv_fd = 1;

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,1)).WillOnce(Return(-1));

	server(1,NULL);

	ASSERT_TRUE(true);
}

TEST( server_test , epoll_create_failed )
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;

	int serv_fd = 1;
	int epoll_sock = -1; 

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,1)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(-1));	

	server(1,NULL);

	ASSERT_TRUE(true);
}

TEST( server_test , epoll_ctl_failed )
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;

	int serv_fd = 1;
	int epoll_sock = 2; 
	

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,1)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,serv_fd,_)).WillOnce(Return(-1));
	server(1,NULL);

	ASSERT_TRUE(true);
}
*/
TEST( reactor_test , epoll_wait_fails )
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;
	os_epoll_wait_mock ewm;

	int serv_fd = 1;
	int epoll_sock = 2; 
	

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,_)).WillOnce(Return(0));

	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,_,_)).Times(2).WillRepeatedly(Return(0));
	EXPECT_FUNCTION_CALL(ewm, (epoll_sock,_,_ ,-1)).WillOnce(Return(-1));

	server(1,NULL);

	ASSERT_TRUE(true);
}

TEST( acceptor_test , accept_cli_fail )
{
	os_socket_mock sm;
	os_bind_mock bm;
	os_listen_mock lm;
	os_epoll_create_mock ecm;
	os_epoll_ctl_mock ectl;
	os_epoll_wait_mock ewm;
	os_accept_mock acm;

	int serv_fd = 1;
	int Maxclients = 100;
	int epoll_sock = 2; 
	int client_fd = -1;

	struct epoll_event e;
	e.events = EPOLLIN;
	e.data.fd = serv_fd;

	EXPECT_FUNCTION_CALL(sm, (_,_,_)).WillOnce(Return(serv_fd));
	EXPECT_FUNCTION_CALL(bm, (serv_fd,_,_)).WillOnce(Return(0));
	EXPECT_FUNCTION_CALL(lm, (serv_fd,_)).WillOnce(Return(0));

	EXPECT_FUNCTION_CALL(ecm, (_)).WillOnce(Return(epoll_sock));
	EXPECT_FUNCTION_CALL(ectl, (epoll_sock,_,_,_)).Times(2).WillRepeatedly(Return(0));
	EXPECT_FUNCTION_CALL(ewm, (epoll_sock,_,_
,-1)).Times(2).WillOnce(DoAll(SetArgPointee<1>(e), Return(1))).WillOnce(Return(-1));

	EXPECT_FUNCTION_CALL(acm , (serv_fd , _,_)).WillOnce(Return(client_fd));

	server(1,NULL);

	ASSERT_TRUE(true);
}


