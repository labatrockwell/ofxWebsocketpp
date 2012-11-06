//
//  ofxWebsocketppEvent.h
//  parisProject
//
//  Created by Lucas Vickers on 9/18/12.
//
//

#ifndef __parisProject__ofxWebsocketppServerEvent__
#define __parisProject__ofxWebsocketppServerEvent__

#include <iostream>

#include "websocketpp.hpp"

#include "ofEvents.h"


namespace ofxWebsocketpp {
    
    // root class
    class websocketEvent : public ofEventArgs {
    public:
        
        typedef websocketpp::server::connection_ptr connection_ptr;
        typedef websocketpp::server::handler::message_ptr message_ptr;
        
        // this is being used as a container class so make a virtual destructor
        virtual ~websocketEvent() { }
        virtual void triggerEvent() { }
    };
    
    // connection events
    // ***************************************************
    class websocketConnectionEvent : public websocketEvent {
    public:
        
        websocketConnectionEvent(websocketpp::server::connection_ptr connection);
        ~websocketConnectionEvent();
        
        static ofEvent <websocketConnectionEvent> handshakeEventNotifier;
        static ofEvent <websocketConnectionEvent> validateEventNotifier;
        static ofEvent <websocketConnectionEvent> openEventNotifier;
        static ofEvent <websocketConnectionEvent> closeEventNotifier;
        static ofEvent <websocketConnectionEvent> failEventNotifier;
        static ofEvent <websocketConnectionEvent> httpEventNotifier;
        
        connection_ptr  connection;
        
    };
    
    class websocketConnectionEventHandshake : public websocketConnectionEvent {
    public:
        websocketConnectionEventHandshake(websocketpp::server::connection_ptr connection)
        : websocketConnectionEvent(connection) { }
        
        void triggerEvent();
    };
    
    class websocketConnectionEventValidate : public websocketConnectionEvent {
    public:
        websocketConnectionEventValidate(connection_ptr connection)
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
    
    class websocketConnectionEventHttp : public websocketConnectionEvent {
    public:
        websocketConnectionEventHttp(connection_ptr connection)
        : websocketConnectionEvent(connection) { }
        
        void triggerEvent();
    };
    
    
    // message event
    // ***************************************************
    class websocketMessageEvent : public websocketEvent {
    public:
        
        websocketMessageEvent(connection_ptr connection,
                              websocketpp::server::handler::message_ptr message);
        ~websocketMessageEvent();
        
        static ofEvent <websocketMessageEvent> messageEventNotifier;
        
        connection_ptr  connection;
        message_ptr     message;
        
        //void cleanEvent();
    };
    
    class websocketMessageEventOnMessage : public websocketMessageEvent {
    public:
        websocketMessageEventOnMessage(connection_ptr connection,
                                       message_ptr message)
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
        
        static ofEvent <websocketPingEvent> pingEventNotifier;
        static ofEvent <websocketPingEvent> pongEventNotifier;
        static ofEvent <websocketPingEvent> pongTimeoutNotifier;
        
        connection_ptr  connection;
        std::string     data;
        
        //void cleanEvent();
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
    
    
};  // end namespace

#endif

