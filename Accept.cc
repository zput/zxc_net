
#include <unistd.h>
#include <stdio.h>
#include <string>

#include"Accept.h"
#include"Channel.h"
#include"InetAddress.h"
#include"EventLoop.h"
#include "Logger.h"

using namespace zxc_net;

namespace {
	
	int createSocket() {
		 int acceptfd=::socket(AF_INET, SOCK_STREAM |SOCK_NONBLOCK |SOCK_CLOEXEC, 0);
		 if (acceptfd == -1)
				printf("Acceptor::socket()\n");
		 return acceptfd;
				
	}
		
}



Accept::Accept(EventLoop* loop,InetAddress* address )
          : loop_(loop),
		    address_(address),
		    acceptfd_(createSocket()),
		    acceptChannel_(new Channel(loop_,acceptfd_)){
	
	int on = 1;
    int ret = ::setsockopt(acceptfd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (ret == -1)
                       //SYSFATAL("Acceptor::setsockopt() SO_REUSEADDR");
	    printf("Acceptor::setsockopt() SO_REUSEADDR");
    ret = ::setsockopt(acceptfd_, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
    if (ret == -1)
                       //SYSFATAL("Acceptor::setsockopt() SO_REUSEPORT");
        printf("Acceptor::setsockopt() SO_REUSEPORT");
	
	
	if(::bind(acceptfd_, address_->getSockaddr(), address_->getSocklen() )<0){
		printf("\nbind error\n");
	} else {
		printf("\nbind success\n");
	}
	if(::listen(acceptfd_ , 10)<0) {
		printf("\nlisten error\n");
	} else {
		printf("\nlisten success\n");
	}
				/*
				printf("bind ip port== %s \n",(address_->toIpPort()).c_str());
				
				printf("\n---------begin----%d---------\n",sizeof(short int));
				struct sockaddr_in addr;
				socklen_t len = sizeof(addr);

				void* any = &addr;
				int sockfd = ::accept4(acceptfd_, static_cast<sockaddr*>(any),
									   &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
				
				printf("\n-----end-------------\n");
				*/

	acceptChannel_->setReadCallback([this](){ handleRead();});
	acceptChannel_->enableReading();
	
}



Accept::~Accept(){
	
	
}

void Accept::handleRead() {
	/*
	 struct inet_address client_address;
	 int client_length=sizeof(inet_address);
	 int clientfd=accept(acceptfd_,(ADDRESS_INET *)&client_address, client_length);
	  // 真实项目怎么报错的   ???   
	  if(clientfd<0) {
		   printf("accept error \n");
		  
	  }
	 
	 newconnectionCallback(clientfd);
	*/ 
	printf("Accept::handleRead\n");
	loop_->assertInLoopThread();
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    void* any = &addr;
    int sockfd = ::accept4(acceptfd_, static_cast<sockaddr*>(any),
                           &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
	if (sockfd == -1) {
		int savedErrno = errno;
	    SYSERR("Acceptor::accept4()");
		switch (savedErrno) {
		case ECONNABORTED:
		case EMFILE:
			break;
		default:
			FATAL("unexpected accept4() error");	
			//printf("\naccept error\n");
		}
	}
	
	if(newconnectionCallback) {
		newconnectionCallback(sockfd);
	}else
	    ::close(sockfd);

}


