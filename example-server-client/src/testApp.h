#pragma once

#include "ofMain.h"

#include "ofxWebsocketpp.h"

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxWebsocketpp::wsServer::server* m_server_ptr;
    ofxWebsocketpp::wsClient::client* m_client_ptr;
    
    
    // Client Callbacks
    void sendBinary(ofxWebsocketpp::wsClient::client::connection_ptr con, const string& binary);
    void sendString(ofxWebsocketpp::wsClient::client::connection_ptr con, const string& str);
    
    void onClientSocketMessage(ofxWebsocketpp::wsClient::websocketMessageEvent &event);
    
    void onClientSocketPing(ofxWebsocketpp::wsClient::websocketPingEvent &event);
    void onClientSocketPong(ofxWebsocketpp::wsClient::websocketPingEvent &event);
    void onClientSocketPongFail(ofxWebsocketpp::wsClient::websocketPingEvent &event);
    
    void onClientSocketHandshake(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);
    void onClientSocketOpen(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);
    void onClientSocketClose(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);
    void onClientSocketFail(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);
		
    
    // Server Callbacks
    void sendString(ofxWebsocketpp::wsServer::server::connection_ptr con, const string& str);
    void sendBinary(ofxWebsocketpp::wsServer::server::connection_ptr con, const string& binary);
    
    void onServerSocketMessage(ofxWebsocketpp::wsServer::websocketMessageEvent &event);
    void onServerSocketHandshake(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onServerSocketValidate(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onServerSocketOpen(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onServerSocketClose(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onServerSocketFail(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onServerSocketHttp(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onServerSocketPing(ofxWebsocketpp::wsServer::websocketPingEvent &event);
    void onServerSocketPong(ofxWebsocketpp::wsServer::websocketPingEvent &event);
    void onServerSocketPongFail(ofxWebsocketpp::wsServer::websocketPingEvent &event);
    
};
