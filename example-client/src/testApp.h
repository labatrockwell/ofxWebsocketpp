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
    
    ofxWebsocketpp::wsClient::client  m_client;
    
    void sendBinary(ofxWebsocketpp::wsClient::client::connection_ptr con, const string& binary);
    void sendString(ofxWebsocketpp::wsClient::client::connection_ptr con, const string& str);
    
    void onSocketMessage(ofxWebsocketpp::wsClient::websocketMessageEvent &event);
    
    void onSocketPing(ofxWebsocketpp::wsClient::websocketPingEvent &event);
    void onSocketPong(ofxWebsocketpp::wsClient::websocketPingEvent &event);
    void onSocketPongFail(ofxWebsocketpp::wsClient::websocketPingEvent &event);

    void onSocketHandshake(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);
    void onSocketOpen(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);
    void onSocketClose(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);
    void onSocketFail(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);
};
