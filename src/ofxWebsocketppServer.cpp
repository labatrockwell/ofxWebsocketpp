//
//  ofxWebsocketppServer.cpp
//  parisProject
//
//  Created by Lucas Vickers on 9/18/12.
//
//

#include "ofxWebsocketppServer.h"
#include "ofxWebsocketppServerHandler.h"

namespace ofxWebsocketpp {
namespace wsServer {
    
    server::server(unsigned short port,
                   unsigned int poolThreads,
                   unsigned int workerThreads)

    : m_port(port),
    m_poolThreads(poolThreads),
    m_workerThreads(workerThreads),
    m_csh(NULL)

    {

    }

    void server::stopServer()
    {
        // the chain of events that follow shut down all threads
        //   and also set m_csh = NULL
        if(m_csh != NULL && m_rs != NULL) {
            // if m_csh or m_rs are null then we are already shut/shutting down
            m_csh->shutdown();
            // TODO close out these connections gracefully
            m_rs->stop(false);
        }
        
        return;
    }

    void server::startServer()
    {
        if( !isThreadRunning() && m_csh == NULL) {
            startThread();
        } else {
            cerr << "Shutdown the server before trying to start." << endl;
        }
    }

    // ofx thread calls this
    void server::threadedFunction()
    {
        event_coordinator rc;
        
        websocketpp::server::handler::ptr h;
        if (m_workerThreads == 0) {
            m_csh = new concurrent_server_handler();
            h = websocketpp::server::handler::ptr(m_csh);
        } else {
            m_csh = new concurrent_server_handler(&rc);
            h = websocketpp::server::handler::ptr(m_csh);
        }
        
        websocketpp::server request_server(h);
        m_rs = &request_server;

        //request_server.alog().unset_level(websocketpp::log::alevel::ALL);
        //request_server.elog().unset_level(websocketpp::log::elevel::ALL);
        
        //request_server.elog().set_level(websocketpp::log::elevel::RERROR);
        //request_server.elog().set_level(websocketpp::log::elevel::FATAL);
        
        // TODO fiure out how to expose this to the end user
        request_server.alog().set_level(websocketpp::log::alevel::ALL);
        request_server.elog().set_level(websocketpp::log::elevel::ALL);
        
        std::list<boost::shared_ptr<boost::thread> > threads;
        if (m_workerThreads > 0) {
            for (size_t i = 0; i < m_workerThreads; i++) {
                
                threads.push_back(
                    boost::shared_ptr<boost::thread>(
                        new boost::thread(boost::bind(&event_processor::process_events, &rc))
                    )
                );
                
            }
            
        }
        
        stringstream ss;
        ss << "Starting WebSocket server on port " << m_port
        << " with thread pool size " << m_poolThreads << " and "
        << m_workerThreads << " worker threads." << std::endl;
        request_server.elog().at(websocketpp::log::alevel::ALL) << ss.str();
        
        request_server.listen(m_port, m_poolThreads);
        
        std::list<boost::shared_ptr<boost::thread> >::iterator it;
        for( it = threads.begin(); it != threads.end(); ++it ) {
            (*it)->join();
        }
        
        cout << "Threads have all exited, now closing server" << endl;
        
        request_server.stop();
        
        cout << "Server has been shut down." << endl;
        
        // set m_csh to NULL so we know it's all done
        m_csh = NULL;
        m_rs = NULL;
    }
}};  // end namespace
