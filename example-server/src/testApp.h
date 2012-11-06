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
    
    ofxWebsocketpp::server *server;

    void sendString(ofxWebsocketpp::server::connection_ptr con, const string& str);
    void sendBinary(ofxWebsocketpp::server::connection_ptr con, const string& binary);
    
    void onSocketMessage(ofxWebsocketpp::websocketMessageEvent &event);
    void onSocketHandshake(ofxWebsocketpp::websocketConnectionEvent &event);
    void onSocketValidate(ofxWebsocketpp::websocketConnectionEvent &event);
    void onSocketOpen(ofxWebsocketpp::websocketConnectionEvent &event);
    void onSocketClose(ofxWebsocketpp::websocketConnectionEvent &event);
    void onSocketFail(ofxWebsocketpp::websocketConnectionEvent &event);
    void onSocketHttp(ofxWebsocketpp::websocketConnectionEvent &event);
    void onSocketPing(ofxWebsocketpp::websocketPingEvent &event);
    void onSocketPong(ofxWebsocketpp::websocketPingEvent &event);
    void onSocketPongFail(ofxWebsocketpp::websocketPingEvent &event);
};
