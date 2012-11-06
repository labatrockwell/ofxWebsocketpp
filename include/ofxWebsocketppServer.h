//
//  ofxWebsocketppDaemon.h
//  parisProject
//
//  Created by Lucas Vickers on 9/18/12.
//
//

#ifndef __parisProject__ofxWebsocketppServer__
#define __parisProject__ofxWebsocketppServer__

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
            
            ofAddListener( websocketMessageEvent::messageEventNotifier,         app, &T::onSocketMessage );
            
            ofAddListener( websocketPingEvent::pingEventNotifier,               app, &T::onSocketPing );
            ofAddListener( websocketPingEvent::pongEventNotifier,               app, &T::onSocketPong );
            ofAddListener( websocketPingEvent::pongTimeoutNotifier,             app, &T::onSocketPongFail );
            
            ofAddListener( websocketConnectionEvent::handshakeEventNotifier,    app, &T::onSocketHandshake );
            ofAddListener( websocketConnectionEvent::validateEventNotifier,     app, &T::onSocketValidate );
            ofAddListener( websocketConnectionEvent::openEventNotifier,         app, &T::onSocketOpen );
            ofAddListener( websocketConnectionEvent::closeEventNotifier,        app, &T::onSocketClose );
            ofAddListener( websocketConnectionEvent::failEventNotifier,         app, &T::onSocketFail );
            ofAddListener( websocketConnectionEvent::httpEventNotifier,         app, &T::onSocketHttp );
            
        }
        
        template<class T>
        void removeListener(T * app){
            
            ofRemoveListener( websocketMessageEvent::messageEventNotifier,     app,  &T::onSocketMessage );
            
            ofRemoveListener( websocketPingEvent::pingEventNotifier,        app, &T::onSocketPing );
            ofRemoveListener( websocketPingEvent::pongEventNotifier,        app, &T::onSocketPong );
            ofRemoveListener( websocketPingEvent::pongTimeoutNotifier,      app, &T::onSocketPongFail );
            
            ofRemoveListener( websocketConnectionEvent::handshakeEventNotifier,   app, &T::onSocketHandshake );
            ofRemoveListener( websocketConnectionEvent::validateEventNotifier,    app, &T::onSocketValidate );
            ofRemoveListener( websocketConnectionEvent::openEventNotifier,        app, &T::onSocketOpen );
            ofRemoveListener( websocketConnectionEvent::closeEventNotifier,       app, &T::onSocketClose );
            ofRemoveListener( websocketConnectionEvent::failEventNotifier,        app, &T::onSocketFail );
            ofRemoveListener( websocketConnectionEvent::httpEventNotifier,        app, &T::onSocketHttp );
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
    
};  // end namespace

#endif
