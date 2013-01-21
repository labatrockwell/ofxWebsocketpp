#include "testApp.h"

using namespace ofxWebsocketpp;

//--------------------------------------------------------------
void testApp::setup(){
    
    m_server_ptr = new wsServer::server(9001, 5, 5);
    m_server_ptr->addListener(this);
    m_server_ptr->startServer();
    
    
    // uncomment the client and they will ping back and forth
    /*
    m_client_ptr = new wsClient::client();
    m_client_ptr->addListener(this);
    m_client_ptr->connect("ws://localhost:9001/");
     */ 
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

void testApp::onServerSocketMessage(wsServer::websocketMessageEvent &event)
{
    cout << "got message event!" << endl;
    event.connection->send("Welcome!");
}

void testApp::onServerSocketHandshake(wsServer::websocketConnectionEvent &event)
{
    cout << "handshake!" << endl;
}

void testApp::onServerSocketValidate(wsServer::websocketConnectionEvent &event)
{
    cout << "validated!" << endl;
}

void testApp::onServerSocketOpen(wsServer::websocketConnectionEvent &event)
{
    cout << "socket open!" << endl;
}

void testApp::onServerSocketClose(wsServer::websocketConnectionEvent &event)
{
    cout << "socket close!" << endl;
}

void testApp::onServerSocketFail(wsServer::websocketConnectionEvent &event)
{
    cout << "socket fail!" << endl;
}

void testApp::onServerSocketHttp(wsServer::websocketConnectionEvent &event)
{
    cout << "http!" << endl;
}

void testApp::onServerSocketPing(wsServer::websocketPingEvent &event)
{
    cout << "ping!" << endl;
}

void testApp::onServerSocketPong(wsServer::websocketPingEvent &event)
{
    cout << "pong!" << endl;
}

void testApp::onServerSocketPongFail(wsServer::websocketPingEvent &event)
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

void testApp::onClientSocketMessage(wsClient::websocketMessageEvent &event)
{
    static int i=0;
    cout << "got message event!  " << (i++) << endl;
    event.connection->send("HI!");
}

void testApp::onClientSocketHandshake(wsClient::websocketConnectionEvent &event)
{
    cout << "handshake!" << endl;
}

void testApp::onClientSocketOpen(wsClient::websocketConnectionEvent &event)
{
    cout << "socket open!" << endl;
    event.connection->send("Hello");
}

void testApp::onClientSocketClose(wsClient::websocketConnectionEvent &event)
{
    cout << "socket close!" << endl;
}

void testApp::onClientSocketFail(wsClient::websocketConnectionEvent &event)
{
    cout << "socket fail!" << endl;
}

void testApp::onClientSocketPing(wsClient::websocketPingEvent &event)
{
    cout << "ping!" << endl;
}

void testApp::onClientSocketPong(wsClient::websocketPingEvent &event)
{
    cout << "pong!" << endl;
}

void testApp::onClientSocketPongFail(wsClient::websocketPingEvent &event)
{
    cout << "pong fail!" << endl;
}



