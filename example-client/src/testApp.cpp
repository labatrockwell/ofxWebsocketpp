#include "testApp.h"

using namespace ofxWebsocketpp::wsClient;

//--------------------------------------------------------------
void testApp::setup(){

    ofSetFrameRate(30);
    
    m_client.addListener(this);
    //m_client.connect("ws://127.0.0.1:9001/");
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
    if( m_client.getState() == websocketpp::session::state::OPEN ) {
        sendString( m_client.getConnection(), "Key pressed." );
    }
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
            m_client.disconnect();
        } else if( x > 200 && x < 400) {
            m_client.connect("ws://localhost:9001/");
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

void testApp::sendString(client::connection_ptr con, const string& str)
{
    con->send(str);
}

void testApp::sendBinary(client::connection_ptr con, const string& binary)
{
    // unfortunately there's no good way to expose the BINARY enum
    // through the wrapper class as it's an Enum
    con->send(binary, websocketpp::frame::opcode::BINARY);
}

void testApp::onClientSocketMessage(websocketMessageEvent &event)
{
    static int i=0;
    cout << "got message event!  " << (i++) << endl;
    //event.connection->send("HI!");
}

void testApp::onClientSocketHandshake(websocketConnectionEvent &event)
{
    cout << "handshake!" << endl;
    event.connection->send("Hello");
}

void testApp::onClientSocketOpen(websocketConnectionEvent &event)
{
    cout << "socket open attempt!" << endl;
}

void testApp::onClientSocketClose(websocketConnectionEvent &event)
{
    cout << "socket close!" << endl;
}

void testApp::onClientSocketFail(websocketConnectionEvent &event)
{
    cout << "socket fail!" << endl;
}

void testApp::onClientSocketPing(websocketPingEvent &event)
{
    cout << "ping!" << endl;
}

void testApp::onClientSocketPong(websocketPingEvent &event)
{
    cout << "pong!" << endl;
}

void testApp::onClientSocketPongFail(websocketPingEvent &event)
{
    cout << "pong fail!" << endl;
}

