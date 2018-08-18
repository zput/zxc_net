
// zxc_echo
// by zxc

#include"InetAddress.h"
#include"EventLoopThread.h"
#include"EventLoop.h"
#include"TcpServerMulti.h"
#include"TcpConnection.h"
#include"Buffer.h"
#include"Logger.h"



void onConnection(const std::shared_ptr<zxc_net::TcpConnection> & conn)
{
	if (conn->connected())
	{
		INFO("onConnection(): new connection [xxx] from threadId:%d\n", syscall(SYS_gettid));
	}
	else
	{
		INFO("onConnection(): connection [s] is down---threadId:%d\n", syscall(SYS_gettid));
	}
}



void messageFunction(const std::shared_ptr<zxc_net::TcpConnection> & conn, zxc_net::Buffer& buf) {

	int p = buf.readableBytes();
	std::string ps = buf.retrieveAllAsString();
	INFO("onMessage(): received %zd bytes from connection [%zd] at %s\n",
		buf.readableBytes(),
		p,
		ps.c_str());
    INFO("client:%s\n",ps.c_str());
	conn->send(ps);

}


void runInThread()
{
	INFO("\nrunInThread(): pid = %d, tid \n", getpid());
}

int main() {
	
	//  setLogLevel(LOG_LEVEL_INFO);
	
	
	INFO("I'm enter\n");
	
	using namespace zxc_net;

	EventLoop loopF;
	EventLoop* loop = &loopF;

	std::string ip = "192.168.5.129";
	uint16_t port = 30005;
	InetAddress local(ip,port);

	TcpServerMulti  serverAll(loop, local);

	serverAll.setConnectionCallback(onConnection);
	serverAll.setMessageCallback(messageFunction);

	serverAll.setNumThread(1);
	serverAll.start();

	loopF.runAfter(Second(2), runInThread);
	loopF.loop();

}



	
	
	
	
	
