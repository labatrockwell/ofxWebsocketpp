//
//  ofxWebsocketppServer.cpp
//  parisProject
//
//  Created by Lucas Vickers on 9/18/12.
//
//

#include "ofxWebsocketppClient.h"
#include "ofxWebsocketppClientHandler.h"

namespace ofxWebsocketpp {
namespace wsClient {

    client::client()
    {
        // TODO rely on the websocketpp states not our internal states
        
        // TODO client thinks it is connected when no server is present
        
        m_state = DISCONNECTED;
        m_endpoint_ptr = NULL;
    }
    
    bool client::connect(std::string uri)
    {
        if(m_state != DISCONNECTED || isThreadRunning() ) {
            
            string errStr = "Called ofxWebsocketpp connect while the client is connected or thread is already running.\nCall disconnect first.\n";
            
            if(m_endpoint_ptr != NULL) {
                m_endpoint_ptr->elog().at(websocketpp::log::elevel::WARN) << errStr;
            } else {
                cerr << errStr << endl;
            }
            
            return false;
        }
        
        m_uri = uri;
        m_state = CONNECTING;
        startThread();
     
        return true;
    }
    
    bool client::disconnect()
    {
        if(m_state != CONNECTED || !isThreadRunning() ) {
            return false;
        }
        
        m_connection_ptr->close(websocketpp::close::status::NORMAL, "");
        m_connection_ptr.reset();
        
        m_endpoint_ptr->stop();
        
        m_endpoint_ptr = NULL;
        m_state = DISCONNECTED;
        
        stopThread();
        
        cout << "Socket closed." << endl;
        return true;
    }

    client::connection_ptr client::getConnection()
    {
        if( m_state == CONNECTED ) {
            return m_connection_ptr;
        } else {
            return NULL;
        }
    }

    // of calls this
    void client::threadedFunction()
    {
        cout << "new threaded func" << endl;
        try {
            websocketpp::client::handler::ptr handler(new client_handler());
            websocketpp::client endpoint(handler);
            
            //endpoint.alog().unset_level(websocketpp::log::alevel::ALL);
            //endpoint.elog().unset_level(websocketpp::log::elevel::ALL);
            
            // TODO figure out how to expose this to the user
            endpoint.alog().set_level(websocketpp::log::alevel::ALL);
            endpoint.elog().set_level(websocketpp::log::elevel::ALL);
            
            m_connection_ptr.reset();
            m_connection_ptr = endpoint.connect(m_uri);
            m_endpoint_ptr = &endpoint;
            
            // TODO check the status of con, and if the connecton is bad
            //  never enter the CONNECTED state, even if for just a second
            m_state = CONNECTED;
            
            endpoint.alog().at(websocketpp::log::alevel::DEVEL) << "endpoint running.\n";
            endpoint.run();
            endpoint.alog().at(websocketpp::log::alevel::DEVEL) << "endpoint finished.\n";
            
            // could be because of a fail, clean up the connection
            m_connection_ptr->close(websocketpp::close::status::NORMAL, "");
            m_connection_ptr.reset();
            
            m_state = DISCONNECTED;
            m_endpoint_ptr = NULL;
            
        } catch (std::exception& e) {
            
            m_endpoint_ptr = NULL;
            m_state = DISCONNECTED;
            cerr << "Exception connecting: " << e.what() << endl;
        }
    }
}};  // end namespaces
