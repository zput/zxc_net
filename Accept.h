
#ifndef ACCEPT_H
#define ACCEPT_H

#include"Callbacks.h"

namespace zxc_net{
	
	
	class InetAddress;
	class Channel;
	class EventLoop;
	
	class Accept{
	     public:
		   Accept(EventLoop* loop, InetAddress* address);
		   ~Accept();
		
		  void handleRead();
		
			
		    void setNewconnectionCallback(NewconnectionCallback  cb ){
				newconnectionCallback = cb;
			}
		
		    void setMessageCallback(MessageCallback cb) {
			    messageCallback =cb;	   
		    }

		    
		
		private:
		    NewconnectionCallback  newconnectionCallback;
			MessageCallback  messageCallback;
	     
		
		private:
		    EventLoop* loop_;
		    InetAddress* address_;
		    int acceptfd_;
            Channel* acceptChannel_;	
            			 
		
	};
	
	
}




#endif
