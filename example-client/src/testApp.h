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
    
    void onClientSocketMessage(ofxWebsocketpp::wsClient::websocketMessageEvent &event);
    
    void onClientSocketPing(ofxWebsocketpp::wsClient::websocketPingEvent &event);
    void onClientSocketPong(ofxWebsocketpp::wsClient::websocketPingEvent &event);
    void onClientSocketPongFail(ofxWebsocketpp::wsClient::websocketPingEvent &event);

    void onClientSocketHandshake(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);
    void onClientSocketOpen(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);
    void onClientSocketClose(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);
    void onClientSocketFail(ofxWebsocketpp::wsClient::websocketConnectionEvent &event);

};
