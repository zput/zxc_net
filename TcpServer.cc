#include"EventLoop.h"
#include"InetAddress.h"

#include"Accept.h"

#include"TcpConnection.h"
#include"TcpServer.h"

using namespace zxc_net;

TcpServer::TcpServer(EventLoop* loop, InetAddress& local)
	:loop_(loop),
	address_(&local),
	accept_(new Accept(loop_, address_)),
	eventLoopThreadPool_( new EventLoopThreadPool(loop_,10) )
{
	accept_->setMessageCallback(messageCallback_);
	// accept_->setNewconnectionCallback([this](){newConnection( );});
	accept_->setNewconnectionCallback(std::bind(&TcpServer::newConnection, this, std::placeholders::_1));
}

 TcpServer::TcpServer (EventLoop* loop, std::string& ip, uint16_t port)
          :loop_(loop),
		   address_( new InetAddress(ip, port)),
		   accept_(new Accept(loop_,address_))  {
	  accept_->setMessageCallback(messageCallback_);
	 // accept_->setNewconnectionCallback([this](){newConnection( );});
	  accept_->setNewconnectionCallback(std::bind(&TcpServer::newConnection, this, std::placeholders::_1));
}
TcpServer::~TcpServer () {
	delete eventLoopThreadPool_;


}



  void TcpServer::newConnection( int connfd ) {
	  
	    
	    
	  //  std::shared_ptr<TcpConnection > conn ( new TcpConnection(loop_,connfd));
		 EventLoop* ioLoop =eventLoopThreadPool_->getOneLoop();

	    std::shared_ptr<TcpConnection > conn(new TcpConnection(ioLoop, connfd));
	    conn->setWriteCallback(writeCallback_);
		conn->setMessageCallback(messageCallback_);
		conn->setConnectionCallback(connectionCallback_);
		conn->setWriteCompleteCallback(writeCompleteCallback_);


	    conn->setremoveConnectionCallback(bind(&TcpServer::removeConnection,this,std::placeholders::_1));

    //	conn->connectEstablished();
		ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished,conn) );
	    connLists_.push_back(conn);
   
  }
   
void TcpServer::removeConnection( const std::shared_ptr<TcpConnection>& conn ) {
	// 当一到到达这个函数 , 证明现在已经在TcpServer中的clientfd 的线程池里的某个线程中(Loop)
	// 我们需要跳到 TcpServer所在的主线程中, acceptfd? 
	loop_->runInLoop( std::bind(&TcpServer::removeConnectionInLoop, this, conn) );
	  
  }
  
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn) {

	for (CONNLISTS::iterator i = connLists_.begin(); i != connLists_.end(); i++) {
		if (*i == conn) {
			printf("\ntest\n");
			connLists_.erase(i);
			printf("\ntest2\n");
			break;
		}
	}
	printf("\ntest3\n");
	EventLoop* ioLoop = conn->getLoop();

	ioLoop->queueInLoop(std::bind(&TcpConnection::destoryConn, conn));
	printf("\nTcpServer::removeConnection ---close \n");


}
  
  
  
  
  
  
  
  
  
  
  
  