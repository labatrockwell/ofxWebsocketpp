#include "testApp.h"

using namespace ofxWebsocketpp::wsServer;

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetWindowShape(400, 200);
    
    server = new wsServer::server(9001, 1, 1);
    server->addListener(this);
    server->startServer();
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
            server->stopServer();
        } else if( x > 200 && x < 400) {
            server->startServer();
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

void testApp::onSocketMessage(websocketMessageEvent &event)
{
    cout << "got message event!" << endl;
    event.connection->send("Welcome!");
}

void testApp::onSocketHandshake(websocketConnectionEvent &event)
{
    cout << "handshake!" << endl;
}

void testApp::onSocketValidate(websocketConnectionEvent &event)
{
    cout << "validated!" << endl;
}

void testApp::onSocketOpen(websocketConnectionEvent &event)
{
    cout << "socket open!" << endl;
}

void testApp::onSocketClose(websocketConnectionEvent &event)
{
    cout << "socket close!" << endl;
}

void testApp::onSocketFail(websocketConnectionEvent &event)
{
    cout << "socket fail!" << endl;
}

void testApp::onSocketHttp(websocketConnectionEvent &event)
{
    cout << "http!" << endl;
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
