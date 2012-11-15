#include "testApp.h"

using namespace ofxWebsocketpp;

//--------------------------------------------------------------
void testApp::setup(){

    client = new wsClient::client();
    
    
    //server = new server::server(9001, 1, 1);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

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
// Server Callbacks


void sendString(wsServer::server::connection_ptr con, const string& str)
{
    con->send(str);
}

void sendBinary(wsServer::server::connection_ptr con, const string& binary)
{
    // unfortunately there's no good way to expose the BINARY enum
    // through the wrapper class as it's an Enum
    con->send(binary, websocketpp::frame::opcode::BINARY);
}

void testApp::onSocketMessage(wsServer::websocketMessageEvent &event)
{
    cout << "got message event!" << endl;
    event.connection->send("Welcome!");
}

void testApp::onSocketHandshake(wsServer::websocketConnectionEvent &event)
{
    cout << "handshake!" << endl;
}

void testApp::onSocketValidate(wsServer::websocketConnectionEvent &event)
{
    cout << "validated!" << endl;
}

void testApp::onSocketOpen(wsServer::websocketConnectionEvent &event)
{
    cout << "socket open!" << endl;
}

void testApp::onSocketClose(wsServer::websocketConnectionEvent &event)
{
    cout << "socket close!" << endl;
}

void testApp::onSocketFail(wsServer::websocketConnectionEvent &event)
{
    cout << "socket fail!" << endl;
}

void testApp::onSocketHttp(wsServer::websocketConnectionEvent &event)
{
    cout << "http!" << endl;
}

void testApp::onSocketPing(wsServer::websocketPingEvent &event)
{
    cout << "ping!" << endl;
}

void testApp::onSocketPong(wsServer::websocketPingEvent &event)
{
    cout << "pong!" << endl;
}

void testApp::onSocketPongFail(wsServer::websocketPingEvent &event)
{
    cout << "pong fail!" << endl;
}


// *************************************************************
// Client Callbacks

void sendString(wsClient::client::connection_ptr con, const string& str)
{
    con->send(str);
}

void sendBinary(wsClient::client::connection_ptr con, const string& binary)
{
    // unfortunately there's no good way to expose the BINARY enum
    // through the wrapper class as it's an Enum
    con->send(binary, websocketpp::frame::opcode::BINARY);
}

void testApp::onSocketMessage(wsClient::websocketMessageEvent &event)
{
    static int i=0;
    cout << "got message event!  " << (i++) << endl;
    event.connection->send("HI!");
}

void testApp::onSocketHandshake(wsClient::websocketConnectionEvent &event)
{
    cout << "handshake!" << endl;
}

void testApp::onSocketOpen(wsClient::websocketConnectionEvent &event)
{
    cout << "socket open!" << endl;
    event.connection->send("Hello");
}

void testApp::onSocketClose(wsClient::websocketConnectionEvent &event)
{
    cout << "socket close!" << endl;
}

void testApp::onSocketFail(wsClient::websocketConnectionEvent &event)
{
    cout << "socket fail!" << endl;
}

void testApp::onSocketPing(wsClient::websocketPingEvent &event)
{
    cout << "ping!" << endl;
}

void testApp::onSocketPong(wsClient::websocketPingEvent &event)
{
    cout << "pong!" << endl;
}

void testApp::onSocketPongFail(wsClient::websocketPingEvent &event)
{
    cout << "pong fail!" << endl;
}



