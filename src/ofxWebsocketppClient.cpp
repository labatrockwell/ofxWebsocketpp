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

        // don't use clean close in threaded environment
        m_endpoint_ptr->stop(false);
        m_endpoint_ptr = NULL;
        m_state = DISCONNECTED;
        stopThread();
        cout << "Socket closed." << endl;
        return true;
    }


    // of calls this
    void client::threadedFunction()
    {
        try {
            websocketpp::client::handler::ptr handler(new client_handler());
            websocketpp::client::connection_ptr con;
            websocketpp::client endpoint(handler);
            
            //endpoint.alog().unset_level(websocketpp::log::alevel::ALL);
            //endpoint.elog().unset_level(websocketpp::log::elevel::ALL);
            
            // TODO figure out how to expose this to the user
            endpoint.alog().set_level(websocketpp::log::alevel::ALL);
            endpoint.elog().set_level(websocketpp::log::elevel::ALL);
            
            con = endpoint.connect(m_uri);
            m_endpoint_ptr = &endpoint;
            
            // TODO check the status of con, and if the connecton is bad
            //  never enter the CONNECTED state, even if for just a second
            m_state = CONNECTED;
            
            endpoint.alog().at(websocketpp::log::alevel::DEVEL) << "endpoint running.\n";
            endpoint.run();
            endpoint.alog().at(websocketpp::log::alevel::DEVEL) << "endpoint finished.\n";
            
            m_state = DISCONNECTED;
            m_endpoint_ptr = NULL;
            
        } catch (std::exception& e) {
            
            m_endpoint_ptr = NULL;
            m_state = DISCONNECTED;
            cerr << "Exception connecting: " << e.what() << endl;
        }
    }
}};  // end namespaces
