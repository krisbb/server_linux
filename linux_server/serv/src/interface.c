#include"interface.h"
#include"os.h"
/////////
#include<net/if.h>
#include<net/if_arp.h>

static void add_ipv4(struct ifaddrs * ifa, struct interface * ifs)//
{
	char host[1024], * netmask;
	int s;
   struct sockaddr_in * sa;
	
	os_memset(&host , 0 , 1024);
   s = os_getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
				 host , 128,
				 NULL, 0, NI_NUMERICHOST);

	if(s == 0)
		sprintf(ifs->IPv4 , "%s" , host );
	
	sa = (struct sockaddr_in *) ifa->ifa_netmask;
	netmask = inet_ntoa(sa->sin_addr);
	sprintf(ifs->Netmask, "%s" , netmask );
	
	return;
}

static void add_ipv6(struct ifaddrs * ifa, struct interface * ifs)//
{
	int s,l;
	char host[1024], * str;
 
	os_memset(&host , 0 , 1024);
	s = os_getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in6),
				 host , 128,
				 NULL, 0, NI_NUMERICHOST);

	if(s == 0)
	{
		str = strchr(host , '%');
		l = (str - host )+1;
	
		if( l != 0 )
			snprintf(ifs->IPv6, l , "%s" , host);	
	}

}

static void add_haddr(struct ifaddrs * ifa, struct interface * ifs)//
{
	struct sockaddr * tmp;
	tmp = (struct sockaddr *) ifa->ifa_addr;
	sprintf(ifs->Mac, "%02x:%02x:%02x:%02x:%02x:%02x",
				(unsigned char) tmp->sa_data[10],
				(unsigned char) tmp->sa_data[11],
				(unsigned char) tmp->sa_data[12],	
				(unsigned char) tmp->sa_data[13],
				(unsigned char) tmp->sa_data[14],
				(unsigned char) tmp->sa_data[15]	
			);
}

static struct interface  * fill_interfaces()//
{
	struct ifaddrs * ifaddr, *ifa;
	struct interface * root = NULL;
	struct interface * tmpifs;

	if( os_getifaddrs(&ifaddr) == -1 ){
		perror("getifaddrs");
		return NULL;
	}

	for ( ifa = ifaddr; ifa != NULL ; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;

		
		// check if interface exist in linked list
		for( tmpifs = root ; tmpifs != NULL ; tmpifs = tmpifs->next){		
			if( 0 == strcmp(tmpifs->name,ifa->ifa_name))
				 break;			 			
		}
		
		//if doesnt exist create and add interface
		if( tmpifs == NULL )	{
			tmpifs =  os_malloc( sizeof( * tmpifs) );
			//add to linked list;
			sprintf( tmpifs->name ,"%s", ifa->ifa_name);
			sprintf( tmpifs->IPv4 ,"%s", " ");
			sprintf( tmpifs->IPv6 ,"%s", " ");
			sprintf( tmpifs->Netmask ,"%s", " ");
			tmpifs->Status =  ifa->ifa_flags & IFF_UP ? UP  : DOWN ;
			tmpifs->next = NULL;

			struct interface * i;
			i = root ;
		
			if( i == NULL )
					root = tmpifs;
			else{
				while(i->next != NULL)
					i = i->next;
		
				i->next = tmpifs;
			}
		}

		switch(ifa->ifa_addr->sa_family)
		{
			case AF_INET:
				add_ipv4(ifa,tmpifs);
			 break;

			case AF_INET6:
				add_ipv6(ifa,tmpifs);
			 break;

			case AF_PACKET:
				add_haddr(ifa,tmpifs);
			 break;
			
			default:
			 break;
		}	

	}

	freeifaddrs(ifaddr);
	return root;
}

static void free_interfaces( struct interface * ifs )//
{
	struct interface * next;

	while( ifs != NULL )
	{
		next = ifs->next;
		os_free(ifs);
		ifs = next;
	}

	return;
}

char * get_available_interfaces()//
{	
	int i = 0;
	struct ifaddrs * ifaddr, * ifa;
	char * buffer = os_malloc( sizeof(char) * 999);

	if( buffer == NULL){
		perror("Memory error");
		return "Server Error";
	}

	if(os_getifaddrs(&ifaddr) == -1){
		perror("getifaddrs");
		return "Error getifadrs";
	}

	for( ifa = ifaddr; ifa != NULL ; ifa = ifa->ifa_next){
		if(ifa->ifa_addr == NULL )
			continue;

		if(ifa->ifa_addr->sa_family == AF_PACKET)
			i += sprintf(buffer + i , "%s " ,ifa->ifa_name);
		}

	freeifaddrs(ifaddr);
	return buffer;		
}

char * get_all_interfaces()//
{
	struct interface * ifs, * root;
	int i = 0;
	char * buffer = os_malloc( sizeof(char) * 999);

	if( buffer == NULL){
		perror("Memory error");
		return "Server Error";
	}

	root = fill_interfaces();

	for( ifs = root; ifs != NULL ; ifs = ifs->next){
		 sprintf( buffer + i  ,
			"Name:%s \nIPv4:%s Netmask:%s \nIPv6:%s \n"
			 "MAC:%s \nSTATUS:%s \n\n",
								  ifs->name, 
								  ifs->IPv4,
								  ifs->Netmask ,
								  ifs->IPv6 ,
								  ifs->Mac ,
								  ifs->Status ? "UP" : "DOWN" 
						);
			i = strlen(buffer);
		}

	free_interfaces(root);

	return buffer;
}

char * get_interface(char * name , int flags )//
{
	struct interface * ifs, * root;
	int i = 0;
	char * buffer = os_malloc( sizeof(char) * 999);
	
	if( buffer == NULL){
		perror("Memory error");
		return "Server Error";
	}
	
	root = fill_interfaces();

	// refactory?
	// char[][] { "name" , "mac ... } 
	// for i=0; i<5 i++ 
	// if ( ( flag >> i) & 0x01 == NULL ) continue ;

	for(ifs = root ; ifs != NULL ; ifs = ifs->next)
		if( strcmp( ifs->name , name) == 0)
				break;
	if(ifs == NULL){
		sprintf(buffer , "%s" , "No such Device");
		return buffer;
	}
	
	if( flags & 0x01 )
	i += sprintf(buffer + i, "Name:%s \n", ifs->name );
	if( flags & 0x02)
	i += sprintf(buffer + i, "IPv4:%s \nNetmask:%s \n",
					 ifs->IPv4 , ifs->Netmask);	
	if( flags & 0x04 )
	i += sprintf(buffer + i, "IPv6:%s \n", ifs->IPv6 );
	if( flags & 0x08 )
	i += sprintf(buffer + i, "Mac:%s \n", ifs->Mac );
	if( flags & 0x10)
	i += sprintf(buffer + i, "Status:%s \n", ifs->Status ? "UP" : "DOWN" );
	
	free_interfaces(root);
	return buffer;
}

char * set_MAC( char * name , char * MAC )//
{
	int sock;
	struct ifreq ifr;
	os_memset(&ifr , 0 , sizeof(ifr));

	if( MAC == NULL )
		return "None Mac addr";

	sscanf( MAC , "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
				&ifr.ifr_ifru.ifru_hwaddr.sa_data[0],
				&ifr.ifr_ifru.ifru_hwaddr.sa_data[1],
				&ifr.ifr_ifru.ifru_hwaddr.sa_data[2],
				&ifr.ifr_ifru.ifru_hwaddr.sa_data[3],
				&ifr.ifr_ifru.ifru_hwaddr.sa_data[4],
				&ifr.ifr_ifru.ifru_hwaddr.sa_data[5]);


	sock = os_socket(AF_INET, SOCK_STREAM , 0 );

	if( sock < 0 )
	{
		perror("Socket MAC");
		return "ERROR IN SET MAC ";
	}

   memcpy(ifr.ifr_name, name , strlen(name));
	ifr.ifr_name[strlen(name)] = '\0';
	
	ifr.ifr_ifru.ifru_hwaddr.sa_family = ARPHRD_ETHER;

	if(os_ioctl(sock,SIOCSIFHWADDR,&ifr) == -1)
	{
		perror("Error MAC ioctl");
		os_close(sock);
		return "ERROR IN SET MAC";
	}	

	os_close(sock);
	
	return "MAC CHANGED";
}

char * set_IP_MASK( char * name , char * IP , char * MASK )//
{
	int sock;
	struct ifreq ifr;
	struct sockaddr_in * addr;

	os_memset(&ifr, 0 , sizeof(ifr));
   
  	ifr.ifr_addr.sa_family = AF_INET;

	addr = (struct sockaddr_in *) &ifr.ifr_addr;

	if(inet_pton(AF_INET, IP , &addr->sin_addr) != 1)
		return "ERROR WRONG IP";

	sock = os_socket(AF_INET, SOCK_STREAM , 0 );

	if( sock < 0 )
	{
		perror("ERROR SOCKET SET IP");
		return "ERROR SET SOCKET";
	}

   memcpy(ifr.ifr_name, name , strlen(name));
	ifr.ifr_name[strlen(name)] = '\0';
	
	if(os_ioctl(sock,SIOCSIFADDR,&ifr) == -1)
	{
		perror("ERROR SET IP IOCTL");
		os_close(sock);
		return "ERROR SET IP IOCTL";
	}	

	addr = (struct sockaddr_in *) &ifr.ifr_netmask;
	
	if(inet_pton(AF_INET, MASK , &addr->sin_addr) != 1)
	{
		os_close(sock);
		return "ERROR WRONG MASK";
	}
	
	if(os_ioctl(sock,SIOCSIFNETMASK,&ifr) == -1)
	{
		perror("ERROR IN SET MASK");
		os_close(sock);
		return "ERROR SET MASK IOCTL";
	}

	os_close(sock);

	return "IP & MASK CHANGED";	
}
