//
//  ofxWebsocketppThreaded.cpp
//  parisServer
//
//  Created by Lucas Vickers on 9/17/12.
//
//

#include "ofxWebsocketppServerHandler.h"

#include "websocketpp.hpp"

#include "ofEvents.h"
#include "ofxWebsocketppServerEvent.h"

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include <cstring>
#include <sstream>
#include <iostream>


namespace ofxWebsocketpp {
    
    
    using websocketpp::server;
    
    
    // ************************************
    // event_coordinator
    // ************************************
    
    event_coordinator::event_coordinator()
    : m_running(true)
    {
        
    }
    
    void event_coordinator::shutdown()
    {
        m_running = false;
        // wake up all the threads
        m_cond.notify_all();
    }
    
    void event_coordinator::add_event( websocketEvent *event )
    {
        //std::cout << "queued event" << std::endl;
        
        boost::unique_lock<boost::mutex> lock(m_lock);
        m_events.push(event);
        lock.unlock();
        m_cond.notify_one();
    }
    
    
    websocketEvent* event_coordinator::get_event()
    {
        //std::cout << "un-queued event" << std::endl;
        
        boost::unique_lock<boost::mutex> lock(m_lock);
        
        // probably only needed after wait, but just so we don't get stuck
        if( !m_running ) {
            return NULL;
        }
        
        while( m_events.empty() && m_running ) {
            m_cond.wait(lock);
        }
        
        // woke up on terminate
        if( !m_running ) {
            return NULL;
        }
        
        websocketEvent *event = m_events.front();
        m_events.pop();
        
        return event;
    }
    
    
    // ************************************
    // event_processor
    // ************************************
    
    void event_processor::process_events(event_coordinator* coordinator)
    {
        websocketEvent *event;
        
        while (1) {
            event = coordinator->get_event();
            // null events means it's time to shut down
            if( event == NULL ) {
                cout << "Returning from processor thread." << endl;
                return;
            }
            // class majic!
            event->triggerEvent();
            delete (event);     // TODO error-prone memory management.  Perhaps shared pointed instead?
        }
    }
    
    
    // ************************************
    // concurrent_server_handler
    // ************************************
    
    concurrent_server_handler::concurrent_server_handler(event_coordinator *c)
    : m_coordinator(c), m_shuttingDown(false)
    {
    
    }
    
    concurrent_server_handler::concurrent_server_handler()
    : m_coordinator(NULL), m_shuttingDown(false)
    {
    
    }

    
    void concurrent_server_handler::shutdown()
    {
        // protect against multiple calls
        if( !m_shuttingDown ) {
            m_coordinator->shutdown();
            m_shuttingDown = true;
        }
    }
    
    
    void concurrent_server_handler::on_message(connection_ptr con, message_ptr msg)
    {
        if(m_coordinator) {
            m_coordinator->add_event(new websocketMessageEventOnMessage(con, msg));
        } else {
            websocketMessageEventOnMessage(con, msg).triggerEvent();
        }
    }
    
    
    
    void concurrent_server_handler::on_handshake_init (connection_ptr con)
    {
        if(m_coordinator) {
            m_coordinator->add_event(new websocketConnectionEventHandshake(con));
        } else {
            websocketConnectionEventHandshake(con).triggerEvent();
        }
    }
    
    void concurrent_server_handler::validate (connection_ptr con)
    {
        if(m_coordinator) {
            m_coordinator->add_event(new websocketConnectionEventValidate(con));
        } else {
            websocketConnectionEventValidate(con).triggerEvent();
        }
    }
    
    void concurrent_server_handler::on_open (connection_ptr con)
    {
        if(m_coordinator) {
            m_coordinator->add_event(new websocketConnectionEventOpen(con));
        } else {
            websocketConnectionEventOpen(con).triggerEvent();
        }
        
        m_connections.insert(con);
    }
    
    void concurrent_server_handler::on_close (connection_ptr con)
    {
        if(m_coordinator) {
            m_coordinator->add_event(new websocketConnectionEventClose(con));
        } else {
            websocketConnectionEventClose(con).triggerEvent();
        }
        
        m_connections.erase(con);
    }
    
    void concurrent_server_handler::on_fail (connection_ptr con)
    {
        if(m_coordinator) {
            m_coordinator->add_event(new websocketConnectionEventFail(con));
        } else {
            websocketConnectionEventFail(con).triggerEvent();
        }
        
        int deletes = m_connections.erase(con);
        
        con->elog()->at(websocketpp::log::elevel::INFO) << "on_fail deleted "
        << deletes << " connections." << websocketpp::log::endl;
        
    }
    
    void concurrent_server_handler::http (connection_ptr con)
    {
        if(m_coordinator) {
            m_coordinator->add_event(new websocketConnectionEventHttp(con));
        } else {
            websocketConnectionEventHttp(con).triggerEvent();
        }
    }
    
    
    bool concurrent_server_handler::on_ping (connection_ptr con, std::string data)
    {
        if(m_coordinator) {
            m_coordinator->add_event(new websocketPingEventPing(con, data));
        } else {
            websocketPingEventPing(con, data).triggerEvent();
        }
        
        return true;
    }
    
    void concurrent_server_handler::on_pong (connection_ptr con, std::string data)
    {
        if(m_coordinator) {
            m_coordinator->add_event(new websocketPingEventPong(con, data));
        } else {
            websocketPingEventPong(con, data).triggerEvent();
        }
    }
    
    void concurrent_server_handler::on_pong_timeout (connection_ptr con, std::string data)
    {
        if(m_coordinator) {
            m_coordinator->add_event(new websocketPingEventPongTimeout(con, data));
        } else {
            websocketPingEventPongTimeout(con, data).triggerEvent();
        }
    }
    
    
    
};  // end namespace
