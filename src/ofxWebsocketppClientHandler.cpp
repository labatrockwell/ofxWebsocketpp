//
//  ofxWebsocketppThreaded.cpp
//  parisServer
//
//  Created by Lucas Vickers on 9/17/12.
//
//

#include "ofxWebsocketppClientHandler.h"

#include "websocketpp.hpp"

#include "ofEvents.h"
#include "ofxWebsocketppClientEvent.h"

#include <cstring>
#include <sstream>
#include <iostream>


namespace ofxWebsocketpp {
namespace wsClient{
    
    
    using websocketpp::role::client;
    
    
    void client_handler::on_message(connection_ptr con, message_ptr msg)
    {
        websocketMessageEventOnMessage(con, msg).triggerEvent();
    }
    
    void client_handler::on_handshake_init (connection_ptr con)
    {
        websocketConnectionEventHandshake(con).triggerEvent();
    }
    
    void client_handler::on_open (connection_ptr con)
    {
        websocketConnectionEventOpen(con).triggerEvent();
    }
    
    void client_handler::on_close (connection_ptr con)
    {
        websocketConnectionEventClose(con).triggerEvent();
    }
    
    void client_handler::on_fail (connection_ptr con)
    {
        websocketConnectionEventFail(con).triggerEvent();
    }
    
    
    bool client_handler::on_ping (connection_ptr con, std::string data)
    {
        websocketPingEventPing(con, data).triggerEvent();
        return true;
    }
    
    void client_handler::on_pong (connection_ptr con, std::string data)
    {
        websocketPingEventPong(con, data).triggerEvent();
    }
    
    void client_handler::on_pong_timeout (connection_ptr con, std::string data)
    {
        websocketPingEventPongTimeout(con, data).triggerEvent();
    }
    
    
    
}};  // end namespace
