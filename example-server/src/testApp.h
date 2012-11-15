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
    
    void onSocketMessage(ofxWebsocketpp::wsServer::websocketMessageEvent &event);
    void onSocketHandshake(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onSocketValidate(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onSocketOpen(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onSocketClose(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onSocketFail(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onSocketHttp(ofxWebsocketpp::wsServer::websocketConnectionEvent &event);
    void onSocketPing(ofxWebsocketpp::wsServer::websocketPingEvent &event);
    void onSocketPong(ofxWebsocketpp::wsServer::websocketPingEvent &event);
    void onSocketPongFail(ofxWebsocketpp::wsServer::websocketPingEvent &event);
};
