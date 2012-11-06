//
//  ofxWebsocketpp.h
//  parisServer
//
//  Created by Lucas Vickers on 9/17/12.
//
//

#ifndef __parisServer__ofxWebsocketppServerHandler__
#define __parisServer__ofxWebsocketppServerHandler__


#include "websocketpp.hpp"

#include "ofxWebsocketppServerEvent.h"
#include "ofEvents.h"

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include <cstring>
#include <sstream>
#include <iostream>


namespace ofxWebsocketpp {
    
    
    
    
    // The coordinator is a simple wrapper around an STL queue. add_event inserts
    // a new request. get_event returns the next available request and blocks
    // (using condition variables) in the case that the queue is empty.
    class event_coordinator {
    public:
        
        event_coordinator();
        
        void add_event( websocketEvent *event );
        
        void shutdown();
        
        websocketEvent* get_event();
        
    private:
        std::queue< websocketEvent* >   m_events;
        boost::mutex                    m_lock;
        boost::condition_variable       m_cond;
        
    protected:
        bool                            m_running;
    };
    
    
    
    class event_processor {
    public:
        
        event_processor() { }
        
        //private:
        // process_events is the main function for a processing thread. It loops
        // forever reading requests, processing them serially, then reading another
        // request.
        static void process_events(event_coordinator* coordinator);
    };
    
    
    // The WebSocket++ handler in this case reads messages from connections and packs
    // connection pointer + message into a request struct and passes it off to the
    // coordinator.
    class concurrent_server_handler : public websocketpp::server::handler {
    public:
        
        concurrent_server_handler(event_coordinator *c);
        
        concurrent_server_handler();
        
        void shutdown();
        
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
        event_coordinator           *m_coordinator;
        std::set<connection_ptr>    m_connections;
        bool                        m_shuttingDown;
    };
    
    
    
};  // end namespace



#endif
