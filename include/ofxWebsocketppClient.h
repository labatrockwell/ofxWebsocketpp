//
//  ofxWebsocketppDaemon.h
//  parisProject
//
//  Created by Lucas Vickers on 9/18/12.
//
//

#ifndef __parisProject__ofxWebsocketppClient__
#define __parisProject__ofxWebsocketppClient__

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

        // LV TODO figure out how we can let user pick which functions they want
        template<class T>
        void addListener(T * app){
            
            ofAddListener( websocketMessageEvent::messageEventNotifier,         app, &T::onSocketMessage );
            
            ofAddListener( websocketPingEvent::pingEventNotifier,               app, &T::onSocketPing );
            ofAddListener( websocketPingEvent::pongEventNotifier,               app, &T::onSocketPong );
            ofAddListener( websocketPingEvent::pongTimeoutNotifier,             app, &T::onSocketPongFail );
            
            ofAddListener( websocketConnectionEvent::handshakeEventNotifier,    app, &T::onSocketHandshake );
            ofAddListener( websocketConnectionEvent::openEventNotifier,         app, &T::onSocketOpen );
            ofAddListener( websocketConnectionEvent::closeEventNotifier,        app, &T::onSocketClose );
            ofAddListener( websocketConnectionEvent::failEventNotifier,         app, &T::onSocketFail );
            
        }
        
        template<class T>
        void removeListener(T * app){
            
            ofRemoveListener( websocketMessageEvent::messageEventNotifier,      app, &T::onSocketMessage );
            
            ofRemoveListener( websocketPingEvent::pingEventNotifier,            app, &T::onSocketPing );
            ofRemoveListener( websocketPingEvent::pongEventNotifier,            app, &T::onSocketPong );
            ofRemoveListener( websocketPingEvent::pongTimeoutNotifier,          app, &T::onSocketPongFail );
            
            ofRemoveListener( websocketConnectionEvent::handshakeEventNotifier, app, &T::onSocketHandshake );
            ofRemoveListener( websocketConnectionEvent::openEventNotifier,      app, &T::onSocketOpen );
            ofRemoveListener( websocketConnectionEvent::closeEventNotifier,     app, &T::onSocketClose );
            ofRemoveListener( websocketConnectionEvent::failEventNotifier,      app, &T::onSocketFail );
        }
        
         
    private:
        void threadedFunction();
        
        string m_uri;
        STATE m_state;
        
        websocketpp::client* m_endpoint_ptr;
        
    };
    
};  // end namespace

#endif
