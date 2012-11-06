#pragma once

#include "ofMain.h"

#include "ofxWebsocketppClient.h"


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
    
    ofxWebsocketpp::client  client;
    
    void sendBinary(ofxWebsocketpp::client::connection_ptr con, const string& binary);
    void sendString(ofxWebsocketpp::client::connection_ptr con, const string& str);
    
    void onSocketMessage(ofxWebsocketpp::websocketMessageEvent &event);
    
    void onSocketPing(ofxWebsocketpp::websocketPingEvent &event);
    void onSocketPong(ofxWebsocketpp::websocketPingEvent &event);
    void onSocketPongFail(ofxWebsocketpp::websocketPingEvent &event);

    void onSocketHandshake(ofxWebsocketpp::websocketConnectionEvent &event);
    void onSocketOpen(ofxWebsocketpp::websocketConnectionEvent &event);
    void onSocketClose(ofxWebsocketpp::websocketConnectionEvent &event);
    void onSocketFail(ofxWebsocketpp::websocketConnectionEvent &event);
};
