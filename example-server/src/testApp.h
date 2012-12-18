#pragma once

#include "ofMain.h"

#include "ofxWebsocketppServer.h"

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
		
    // **************************
    
    ofxWebsocketpp::wsServer::server *m_server_ptr;

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
