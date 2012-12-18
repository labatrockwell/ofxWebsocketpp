//
//  ofxWebsocketpp.h
//  parisServer
//
//  Created by Lucas Vickers on 9/17/12.
//
//

#ifndef ofxWebsocketppClientHandler__
#define ofxWebsocketppClientHandler__

// remove MacTypes.h clash with boost
#ifdef nil
#undef nil
#endif

#include "roles/client.hpp"
#include "websocketpp.hpp"

#include "ofxWebsocketppClientEvent.h"
#include "ofEvents.h"

#include <cstring>
#include <sstream>
#include <iostream>


namespace ofxWebsocketpp {
namespace wsClient {
    
    // The WebSocket++ handler in this case reads messages from connections and packs
    // connection pointer + message into a request struct and passes it off to the
    // coordinator.
    class client_handler : public websocketpp::client::handler {
    public:
        
        client_handler() { }
        
        void on_message(connection_ptr con, message_ptr msg);
        void on_handshake_init (connection_ptr con);
        void on_open (connection_ptr con);
        void on_close (connection_ptr con);
        void on_fail (connection_ptr con);
        bool on_ping (connection_ptr con, std::string data);
        void on_pong (connection_ptr con, std::string data);
        void on_pong_timeout (connection_ptr con, std::string data);
        
    private:
        
    };
    
    
    
}};  // end namespaces



#endif
