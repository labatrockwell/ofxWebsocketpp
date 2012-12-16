//
//  ofxWebsocketppDaemon.h
//  parisProject
//
//  Created by Lucas Vickers on 9/18/12.
//
//

#ifndef ofxWebsocketppServer__
#define ofxWebsocketppServer__

#include <iostream>

#include "ofxWebsocketppServerEvent.h"
#include "ofxWebsocketppServerHandler.h"

#include "websocketpp.hpp"

#include "ofMain.h"
#include "ofEvents.h"


/*
 
 This wraps the ofxWebsocketpp class and launches an ofxThread.
 This is different than the boost native threads used in ofxWebsocketpp,
 and we need to make sure we use the correct thread locks
 
 */
 
namespace ofxWebsocketpp {
namespace wsServer{

    // unfortunately you can't expose an enum through typedef
    //typedef websocketpp::frame::opcode::BINARY OPCODE_BINARY;
    
    // This is the main class, it starts up the server and the daemon thread and handles all
    // requests in the background
    class server : public ofThread{
    public:

        server(unsigned short port = 9001,
               unsigned int poolThreads = 2,  // internal threads for ASIO in/out
               unsigned int workerThreads = 2);   // non ASIO threads that process incoming messages
        
        void startServer();
        void stopServer();

        typedef websocketpp::server::handler::connection_ptr    connection_ptr;
        typedef websocketpp::server::handler::message_ptr       message_ptr;
        
        // will not block
        void broadcast();
        std::set< connection_ptr > getConnections();

        
        // LV TODO figure out how we can let user pick which functions they want
        template<class T>
        void addListener(T * app){
            
            ofAddListener( websocketMessageEvent::messageEventNotifier,         app, &T::onServerSocketMessage );
            
            ofAddListener( websocketPingEvent::pingEventNotifier,               app, &T::onServerSocketPing );
            ofAddListener( websocketPingEvent::pongEventNotifier,               app, &T::onServerSocketPong );
            ofAddListener( websocketPingEvent::pongTimeoutNotifier,             app, &T::onServerSocketPongFail );
            
            ofAddListener( websocketConnectionEvent::handshakeEventNotifier,    app, &T::onServerSocketHandshake );
            ofAddListener( websocketConnectionEvent::validateEventNotifier,     app, &T::onServerSocketValidate );
            ofAddListener( websocketConnectionEvent::openEventNotifier,         app, &T::onServerSocketOpen );
            ofAddListener( websocketConnectionEvent::closeEventNotifier,        app, &T::onServerSocketClose );
            ofAddListener( websocketConnectionEvent::failEventNotifier,         app, &T::onServerSocketFail );
            ofAddListener( websocketConnectionEvent::httpEventNotifier,         app, &T::onServerSocketHttp );
            
        }
        
        template<class T>
        void removeListener(T * app){
            
            ofRemoveListener( websocketMessageEvent::messageEventNotifier,     app,  &T::onServerSocketMessage );
            
            ofRemoveListener( websocketPingEvent::pingEventNotifier,        app, &T::onServerSocketPing );
            ofRemoveListener( websocketPingEvent::pongEventNotifier,        app, &T::onServerSocketPong );
            ofRemoveListener( websocketPingEvent::pongTimeoutNotifier,      app, &T::onServerSocketPongFail );
            
            ofRemoveListener( websocketConnectionEvent::handshakeEventNotifier,   app, &T::onServerSocketHandshake );
            ofRemoveListener( websocketConnectionEvent::validateEventNotifier,    app, &T::onServerSocketValidate );
            ofRemoveListener( websocketConnectionEvent::openEventNotifier,        app, &T::onServerSocketOpen );
            ofRemoveListener( websocketConnectionEvent::closeEventNotifier,       app, &T::onServerSocketClose );
            ofRemoveListener( websocketConnectionEvent::failEventNotifier,        app, &T::onServerSocketFail );
            ofRemoveListener( websocketConnectionEvent::httpEventNotifier,        app, &T::onServerSocketHttp );
        }
        
         
    private:
        void threadedFunction();
        
    private:
        unsigned short              m_port;
        unsigned int                m_workerThreads;
        unsigned int                m_poolThreads;
        concurrent_server_handler*  m_csh;
        websocketpp::server*        m_rs;
        
    };
    
}};  // end namespaces

#endif
