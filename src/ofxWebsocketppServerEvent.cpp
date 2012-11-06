//
//  ofxWebsocketppEvent.cpp
//  parisProject
//
//  Created by Lucas Vickers on 9/18/12.
//
//


#include "ofxWebsocketppServerEvent.h"
#include "ofEvents.h"

// TODO add namespace

namespace ofxWebsocketpp {
    
    // connection events
    // ***************************************************
    websocketConnectionEvent::websocketConnectionEvent(websocketpp::server::connection_ptr connection)
    : connection(connection) {
    }
    
    websocketConnectionEvent::~websocketConnectionEvent() {
    }
    
    ofEvent <websocketConnectionEvent> websocketConnectionEvent::handshakeEventNotifier;
    ofEvent <websocketConnectionEvent> websocketConnectionEvent::validateEventNotifier;
    ofEvent <websocketConnectionEvent> websocketConnectionEvent::openEventNotifier;
    ofEvent <websocketConnectionEvent> websocketConnectionEvent::closeEventNotifier;
    ofEvent <websocketConnectionEvent> websocketConnectionEvent::failEventNotifier;
    ofEvent <websocketConnectionEvent> websocketConnectionEvent::httpEventNotifier;
    
    void websocketConnectionEventHandshake::triggerEvent() {
        websocketConnectionEvent event(connection);
        ofNotifyEvent(handshakeEventNotifier, event);
    }
    
    void websocketConnectionEventValidate::triggerEvent() {
        websocketConnectionEvent event(connection);
        ofNotifyEvent(validateEventNotifier, event);
    }
    
    void websocketConnectionEventOpen::triggerEvent() {
        websocketConnectionEvent event(connection);
        ofNotifyEvent(openEventNotifier, event);
    }
    
    void websocketConnectionEventClose::triggerEvent() {
        websocketConnectionEvent event(connection);
        ofNotifyEvent(closeEventNotifier, event);
    }
    
    void websocketConnectionEventFail::triggerEvent() {
        websocketConnectionEvent event(connection);
        ofNotifyEvent(failEventNotifier, event);
    }
    
    void websocketConnectionEventHttp::triggerEvent() {
        websocketConnectionEvent event(connection);
        ofNotifyEvent(httpEventNotifier, event);
    }
    
    
    // message event
    // ***************************************************
    websocketMessageEvent::websocketMessageEvent(websocketpp::server::connection_ptr connection,
                                                 websocketpp::server::handler::message_ptr message)
    : connection(connection), message(message) {
    }
    
    websocketMessageEvent::~websocketMessageEvent() {
    }
    
    ofEvent <websocketMessageEvent> websocketMessageEvent::messageEventNotifier;
    
    
    void websocketMessageEventOnMessage::triggerEvent() {
        websocketMessageEvent event(connection, message);
        ofNotifyEvent(messageEventNotifier, event);
    }
    
    
    
    // ping events
    // ***************************************************
    websocketPingEvent::websocketPingEvent(websocketpp::server::connection_ptr connection,
                                           std::string &data)
    : connection(connection), data(data) {
    }
    
    websocketPingEvent::~websocketPingEvent() {
    }
    
    
    ofEvent <websocketPingEvent> websocketPingEvent::pingEventNotifier;
    ofEvent <websocketPingEvent> websocketPingEvent::pongEventNotifier;
    ofEvent <websocketPingEvent> websocketPingEvent::pongTimeoutNotifier;
    
    void websocketPingEventPing::triggerEvent() {
        websocketPingEvent event(connection, data);
        ofNotifyEvent(pingEventNotifier, event);
    }
    
    void websocketPingEventPong::triggerEvent() {
        websocketPingEvent event(connection, data);
        ofNotifyEvent(pongEventNotifier, event);
    }
    
    void websocketPingEventPongTimeout::triggerEvent() {
        websocketPingEvent event(connection, data);
        ofNotifyEvent(pongTimeoutNotifier, event);
    }
    
};

