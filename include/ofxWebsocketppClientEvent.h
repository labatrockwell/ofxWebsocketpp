//
//  ofxWebsocketppEvent.h
//  parisProject
//
//  Created by Lucas Vickers on 9/18/12.
//
//

#ifndef ofxWebsocketppClientEvent__
#define ofxWebsocketppClientEvent__

#include <iostream>


// remove MacTypes.h clash with boost
#ifdef nil
#undef nil
#endif

#include "roles/client.hpp"
#include "websocketpp.hpp"

#include "ofEvents.h"


namespace ofxWebsocketpp {
namespace wsClient {
    
    // root class
    class websocketEvent : public ofEventArgs {
    public:
        
        typedef websocketpp::client::handler::connection_ptr    connection_ptr;
        typedef websocketpp::client::handler::message_ptr       message_ptr;
        
        // this is being used as a container class so make a virtual destructor
        virtual ~websocketEvent() { }
    };
    
    // connection events
    // ***************************************************
    class websocketConnectionEvent : public websocketEvent {
    public:
        
        websocketConnectionEvent(connection_ptr connection);
        ~websocketConnectionEvent();
        
        static ofEvent <websocketConnectionEvent> handshakeEventNotifier;
        static ofEvent <websocketConnectionEvent> openEventNotifier;
        static ofEvent <websocketConnectionEvent> closeEventNotifier;
        static ofEvent <websocketConnectionEvent> failEventNotifier;
        
        connection_ptr     connection;
        
    };
    
    class websocketConnectionEventHandshake : public websocketConnectionEvent {
    public:
        websocketConnectionEventHandshake(connection_ptr connection)
        : websocketConnectionEvent(connection) { }
        
        void triggerEvent();
    };
    
    class websocketConnectionEventOpen : public websocketConnectionEvent {
    public:
        websocketConnectionEventOpen(connection_ptr connection)
        : websocketConnectionEvent(connection) { }
        
        void triggerEvent();
    };
    
    class websocketConnectionEventClose : public websocketConnectionEvent {
    public:
        websocketConnectionEventClose(connection_ptr connection)
        : websocketConnectionEvent(connection) { }
        
        void triggerEvent();
    };
    
    class websocketConnectionEventFail : public websocketConnectionEvent {
    public:
        websocketConnectionEventFail(connection_ptr connection)
        : websocketConnectionEvent(connection) { }
        
        void triggerEvent();
    };
    
    
    // message event
    // ***************************************************
    class websocketMessageEvent : public websocketEvent {
    public:
        
        websocketMessageEvent(connection_ptr connection,
                              message_ptr message);
        ~websocketMessageEvent();
        
        static ofEvent <websocketMessageEvent> messageEventNotifier;
        
        connection_ptr          connection;
        message_ptr             message;
        
        //void cleanEvent();
    };
    
    class websocketMessageEventOnMessage : public websocketMessageEvent {
    public:
        websocketMessageEventOnMessage(connection_ptr  connection,
                                       message_ptr       message)
        : websocketMessageEvent(connection, message) { }
        
        void triggerEvent();
    };
    
    
    // ping events
    // ***************************************************
    class websocketPingEvent : public websocketEvent {
    public:
        
        websocketPingEvent(connection_ptr connection,
                           std::string &data);
        ~websocketPingEvent();
        
        static ofEvent <websocketPingEvent>     pingEventNotifier;
        static ofEvent <websocketPingEvent>     pongEventNotifier;
        static ofEvent <websocketPingEvent>     pongTimeoutNotifier;
        
        connection_ptr      connection;
        std::string         data;
        
    };
    
    class websocketPingEventPing : public websocketPingEvent {
    public:
        websocketPingEventPing(connection_ptr connection,
                               std::string &data)
        : websocketPingEvent(connection, data) { }
        
        void triggerEvent();
    };
    
    class websocketPingEventPong : public websocketPingEvent {
    public:
        websocketPingEventPong(connection_ptr connection,
                               std::string &data)
        : websocketPingEvent(connection, data) { }
        
        void triggerEvent();
    };
    
    class websocketPingEventPongTimeout : public websocketPingEvent {
    public:
        websocketPingEventPongTimeout(connection_ptr connection,
                                      std::string &data)
        : websocketPingEvent(connection, data) { }
        
        void triggerEvent();
    };
    
    
}};  // end namespaces

#endif

