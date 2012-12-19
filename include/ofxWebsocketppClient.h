//
//  ofxWebsocketppDaemon.h
//  parisProject
//
//  Created by Lucas Vickers on 9/18/12.
//
//

#ifndef ofxWebsocketppClient__
#define ofxWebsocketppClient__

#include <iostream>

#include "ofxWebsocketppClientEvent.h"

// remove MacTypes.h clash with boost
#ifdef nil
#undef nil
#endif

#include "roles/client.hpp"
#include "websocketpp.hpp"

#include "ofMain.h"
#include "ofEvents.h"


namespace ofxWebsocketpp {
namespace wsClient {
    
    class client : public ofThread{
    public:
        
        typedef websocketpp::client::handler::connection_ptr    connection_ptr;
        typedef websocketpp::client::handler::message_ptr       message_ptr;
        
        enum STATE {CONNECTING, CONNECTED, DISCONNECTED};
        

        client();
        
        STATE getClientState() {
            return m_state;
        }
        
        bool connect(string uri);
        
        // returns false if you try to disconnect while connecting, etc
        bool disconnect();

        connection_ptr getConnection();
        
        // LV TODO figure out how we can let user pick which functions they want
        template<class T>
        void addListener(T * app){
            
            ofAddListener( websocketMessageEvent::messageEventNotifier,         app, &T::onClientSocketMessage );
            
            ofAddListener( websocketPingEvent::pingEventNotifier,               app, &T::onClientSocketPing );
            ofAddListener( websocketPingEvent::pongEventNotifier,               app, &T::onClientSocketPong );
            ofAddListener( websocketPingEvent::pongTimeoutNotifier,             app, &T::onClientSocketPongFail );
            
            ofAddListener( websocketConnectionEvent::handshakeEventNotifier,    app, &T::onClientSocketHandshake );
            ofAddListener( websocketConnectionEvent::openEventNotifier,         app, &T::onClientSocketOpen );
            ofAddListener( websocketConnectionEvent::closeEventNotifier,        app, &T::onClientSocketClose );
            ofAddListener( websocketConnectionEvent::failEventNotifier,         app, &T::onClientSocketFail );
            
        }
        
        template<class T>
        void removeListener(T * app){
            
            ofRemoveListener( websocketMessageEvent::messageEventNotifier,      app, &T::onClientSocketMessage );
            
            ofRemoveListener( websocketPingEvent::pingEventNotifier,            app, &T::onClientSocketPing );
            ofRemoveListener( websocketPingEvent::pongEventNotifier,            app, &T::onClientSocketPong );
            ofRemoveListener( websocketPingEvent::pongTimeoutNotifier,          app, &T::onClientSocketPongFail );
            
            ofRemoveListener( websocketConnectionEvent::handshakeEventNotifier, app, &T::onClientSocketHandshake );
            ofRemoveListener( websocketConnectionEvent::openEventNotifier,      app, &T::onClientSocketOpen );
            ofRemoveListener( websocketConnectionEvent::closeEventNotifier,     app, &T::onClientSocketClose );
            ofRemoveListener( websocketConnectionEvent::failEventNotifier,      app, &T::onClientSocketFail );
        }
        
         
    private:
        void threadedFunction();
        
        string m_uri;
        STATE m_state;
        
        connection_ptr m_connection_ptr;
        
        websocketpp::client* m_endpoint_ptr;
        
    };
    
}};  // end namespaces

#endif
