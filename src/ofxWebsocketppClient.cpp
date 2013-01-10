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
        m_endpoint_ptr = NULL;
    }
    
    websocketpp::session::state::value client::getState()
    {
        if( m_connection ) {
            return m_connection->get_state();
        }
        
        return websocketpp::session::state::CLOSED;
    }
    
    bool client::connect(std::string uri)
    {
        if(m_connection && (m_connection->get_state() != websocketpp::session::state::CLOSED || isThreadRunning()) ) {
            
            string errStr = "Called ofxWebsocketpp connect while the client is != CLOSED or thread is already running.\nCall disconnect first.\n";
            
            if(m_endpoint_ptr != NULL) {
                m_endpoint_ptr->elog().at(websocketpp::log::elevel::WARN) << errStr;
            } else {
                cerr << errStr << endl;
            }
            
            return false;
        }
        
        m_uri = uri;
        startThread();
     
        return true;
    }
    
    bool client::disconnect()
    {
        if(m_connection && m_connection->get_state() == websocketpp::session::state::CLOSED && !isThreadRunning() ) {
            
            string errStr = "Called ofxWebsocketpp disconnect while the client == CLOSED and thread is not running.\n";
            
            if(m_endpoint_ptr != NULL) {
                m_endpoint_ptr->elog().at(websocketpp::log::elevel::WARN) << errStr;
            } else {
                cerr << errStr << endl;
            }
            
            if( m_endpoint_ptr != NULL ) {
                m_connection.reset();
                
                m_endpoint_ptr->stop();
                m_endpoint_ptr = NULL;
            }
            return false;
        }
        if( m_connection ) {
            m_connection->close(websocketpp::close::status::NORMAL, "");
            m_connection.reset();
        }
        
        if( m_endpoint_ptr ) {
            m_endpoint_ptr->stop();
            m_endpoint_ptr = NULL;
        }
        
        stopThread();
        
        cout << "Socket closed." << endl;
        return true;
    }

    client::connection_ptr client::getConnection()
    {
        return m_connection;
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
            
            m_connection.reset();
            m_connection = endpoint.connect(m_uri);
            m_endpoint_ptr = &endpoint;
                        
            endpoint.alog().at(websocketpp::log::alevel::DEVEL) << "endpoint running.\n";
            endpoint.run();
            endpoint.alog().at(websocketpp::log::alevel::DEVEL) << "endpoint finished.\n";
            
            // could be because of a fail, clean up the connection
            if( m_connection ) {
                m_connection->close(websocketpp::close::status::NORMAL, "");
            }
            m_connection.reset();
            
            m_endpoint_ptr = NULL;
            
        } catch (std::exception& e) {
            
            m_endpoint_ptr = NULL;
            cerr << "Exception connecting: " << e.what() << endl;
        }
    }
}};  // end namespaces

