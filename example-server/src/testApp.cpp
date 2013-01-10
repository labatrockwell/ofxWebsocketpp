#include "testApp.h"

using namespace ofxWebsocketpp::wsServer;

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetWindowShape(400, 200);
    ofSetFrameRate(30);
    
    m_server_ptr = new server(9001, 5, 5);
    m_server_ptr->addListener(this);
    m_server_ptr->startServer();
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
    ofDrawBitmapString("Close Server", 25, 50);
    ofDrawBitmapString("Start Server", 225, 50);
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
            m_server_ptr->stopServer();
        } else if( x > 200 && x < 400) {
            m_server_ptr->startServer();
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


void sendString(server::connection_ptr con, const string& str)
{
    con->send(str);
}

void sendBinary(server::connection_ptr con, const string& binary)
{
    // unfortunately there's no good way to expose the BINARY enum
    // through the wrapper class as it's an Enum
    con->send(binary, websocketpp::frame::opcode::BINARY);
}

void testApp::onServerSocketMessage(websocketMessageEvent &event)
{
    cout << "got message event!" << endl;
    event.connection->send("Welcome!");
}

void testApp::onServerSocketHandshake(websocketConnectionEvent &event)
{
    cout << "handshake!" << endl;
}

void testApp::onServerSocketValidate(websocketConnectionEvent &event)
{
    cout << "validated!" << endl;
}

void testApp::onServerSocketOpen(websocketConnectionEvent &event)
{
    cout << "socket open!" << endl;
}

void testApp::onServerSocketClose(websocketConnectionEvent &event)
{
    cout << "socket close!" << endl;
}

void testApp::onServerSocketFail(websocketConnectionEvent &event)
{
    cout << "socket fail!" << endl;
}

void testApp::onServerSocketHttp(websocketConnectionEvent &event)
{
    cout << "http!" << endl;
}

void testApp::onServerSocketPing(websocketPingEvent &event)
{
    cout << "ping!" << endl;
}

void testApp::onServerSocketPong(websocketPingEvent &event)
{
    cout << "pong!" << endl;
}

void testApp::onServerSocketPongFail(websocketPingEvent &event)
{
    cout << "pong fail!" << endl;
}
