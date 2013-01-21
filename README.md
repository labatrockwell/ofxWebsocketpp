************************************************
 ABOUT 
************************************************
* App: ofxWebsocketpp

Description:
* websocketpp wrapper for OpenFrameworks.  Wrapper client runs in it's own thread, server allows multiple threads.  Server has configurable pool threads (operate on server in/out) and worker threads (handle the of callback side work).  


Documentation
* Example client, server, and client-server.
* All examples are obvious, the client-server example needs the client part in testApp.cpp commented out and then client and server will send messages back and forth nonstop.


************************************************
 SETUP 
************************************************
Hardware Requirements:
* A computer of sorts.

Dependencies:
* Boost.  Tested for OS X @ 1.50 (what I had installed), Win 7 @ 1.47 (per websocketpp recommendation)
* websocketpp @ commit 27a6d6f4d337c254c732df57531e9bc3d37d70d8

Installation
* Install boost.  HomeBrew or MacPorts, or just download.  
  * OS X, edit the Project.xcconfig file so that BOOST_LIBS_PATHS and BOOST_HEADERS point to the appropriate locations.
  * Visual studio, 
* Checkout the websocketpp submodule
  - git submodule update

Compilation
* Start with the base examples.  You depend on the websocketpp headers

************************************************
 RUN 
************************************************

* Run client-example and server-example locally.  Click on the red and green boxes in the windows to stop/start and connect/disconnect.


************************************************
 MORE INFO 
************************************************
* To-Dos
  * See GitHub issue tracking

* Troubleshooting
  * 

* Credits
  * websocketpp is from https://github.com/zaphoyd/websocketpp .  They did all the hard work.

* Licensing
  * Open-source (BSD license)

* Notes
  * Please contact me with any issues.


