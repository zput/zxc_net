#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H


#include"Callbacks.h"
#include"Buffer.h"

namespace zxc_net{

class EventLoop;
class Channel;
class Buffer;

class TcpConnection: public std::enable_shared_from_this<TcpConnection>  {
	    public:
		
		   TcpConnection (EventLoop* loop,int conn);
           ~TcpConnection ( );
		
		void handleRead();
		void handleWrite();
		void handleClose();
		
		    void setMessageCallback(MessageCallback cb) {
			    messageCallback_ =cb;	   
		    }
		    void setWriteCallback(WriteCallback cb ) {
			    writeCallback_ = cb;
		    }
			void setConnectionCallback(ConnectionCallback cb ) {
			    connectionCallback_ = cb;
		    }

			void setWriteCompleteCallback(const WriteCompleteCallback& cb)
			{
				writeCompleteCallback_ = cb;
			}

			void setremoveConnectionCallback(removeConnectionCallback cb ) {
			    removeConnection_ = cb;
		    }
			void connectEstablished();
			void destoryConn();

			void  sendInLoop(const std::string& message);
			void send(const std::string& message);

			EventLoop* getLoop() { return loop_;  };

      public:
			bool connected() const { return state_ == kConnected; }
			
	  private:
		   enum StateE { kConnecting, kConnected, kDisconnecting, kDisconnected, };
            void setState(StateE s) {
				state_=s;
			}
			
	  private:
	      		  
		  MessageCallback  messageCallback_;
          WriteCallback    writeCallback_;
		  ConnectionCallback connectionCallback_;
	      removeConnectionCallback  removeConnection_;
		  WriteCompleteCallback   writeCompleteCallback_;
          
      private:
			EventLoop * loop_;
              int connfd_;
              Channel* connChannel_;	
              char* readBuff;
              char* writeBuff;	
              Buffer inputBuffer_;			  
	          Buffer outputBuffer_;
			  StateE state_;
	
};	



}

#endif

