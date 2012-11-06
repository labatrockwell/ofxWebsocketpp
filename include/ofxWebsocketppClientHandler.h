//
//  ofxWebsocketpp.h
//  parisServer
//
//  Created by Lucas Vickers on 9/17/12.
//
//

#ifndef __parisServer__ofxWebsocketppClientHandler__
#define __parisServer__ofxWebsocketppClientHandler__

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
    
    // The WebSocket++ handler in this case reads messages from connections and packs
    // connection pointer + message into a request struct and passes it off to the
    // coordinator.
    class client_handler : public websocketpp::client::handler {
    public:
        
        client_handler() { }
        
        void on_message(connection_ptr con, message_ptr msg);
        void on_handshake_init (connection_ptr con);
        void validate (connection_ptr con);
        void on_open (connection_ptr con);
        void on_close (connection_ptr con);
        void on_fail (connection_ptr con);
        void http (connection_ptr con);
        bool on_ping (connection_ptr con, std::string data);
        void on_pong (connection_ptr con, std::string data);
        void on_pong_timeout (connection_ptr con, std::string data);
        
    private:
        
    };
    
    
    
};  // end namespace



#endif
