LIB_SRC = Channel.cc EventLoop.cc EventLoopThread.cc Poller.cc  TimerQueue.cc TcpServer.cc  Accept.cc TcpConnection.cc   InetAddress.cc   Buffer.cc   TcpServerMulti.cc   ThreadPool.cc   Logger.c    EventLoopThreadPool.h EventLoopThreadPool.cpp                                     
BINARIES =  test7

all: $( )




CXXFLAGS = -O0 -g -std=c++17 -Wall -I ../.. -pthread
LDFLAGS = -lpthread

$(BINARIES):
	g++ $(CXXFLAGS) -o $@ $(LIB_SRC) $(filter %.cc,$^) $(LDFLAGS)

	
test1: test1.cc
test2: test2.cc
test3: test3.cc
test4: test4.cc
test5: test5.cc
test6: test6.cc
test7: test7.cc


