#include "testApp.h"

using namespace ofxWebsocketpp::wsClient;

//--------------------------------------------------------------
void testApp::setup(){

    client.addListener(this);
    client.connect("ws://localhost:9001/");
    ofSetWindowShape(400, 200);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255, 0, 0);
    ofRect(0, 0, 200, 200);
    
    ofSetColor(0, 255, 0);
    ofRect(200, 0, 200, 200);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("Close Client \nConnection", 25, 50);
    ofDrawBitmapString("Open Client \nConnection", 225, 50);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(y > 0 && y < 400) {
        if(x > 0 && x < 200) {
            client.disconnect();
        } else if( x > 200 && x < 400) {
            client.connect("ws://localhost:9001/");
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

// *************************************************************
// *************************************************************
// *************************************************************

void sendString(client::connection_ptr con, const string& str)
{
    con->send(str);
}

void sendBinary(client::connection_ptr con, const string& binary)
{
    // unfortunately there's no good way to expose the BINARY enum
    // through the wrapper class as it's an Enum
    con->send(binary, websocketpp::frame::opcode::BINARY);
}

void testApp::onSocketMessage(websocketMessageEvent &event)
{
    static int i=0;
    cout << "got message event!  " << (i++) << endl;
    event.connection->send("HI!");
}

void testApp::onSocketHandshake(websocketConnectionEvent &event)
{
    cout << "handshake!" << endl;
}

void testApp::onSocketOpen(websocketConnectionEvent &event)
{
    cout << "socket open!" << endl;
    event.connection->send("Hello");
}

void testApp::onSocketClose(websocketConnectionEvent &event)
{
    cout << "socket close!" << endl;
}

void testApp::onSocketFail(websocketConnectionEvent &event)
{
    cout << "socket fail!" << endl;
}

void testApp::onSocketPing(websocketPingEvent &event)
{
    cout << "ping!" << endl;
}

void testApp::onSocketPong(websocketPingEvent &event)
{
    cout << "pong!" << endl;
}

void testApp::onSocketPongFail(websocketPingEvent &event)
{
    cout << "pong fail!" << endl;
}

