************************************************
 ABOUT 
************************************************
* App: ofxWebsocketpp

Description:
* websocketpp wrapper for OpenFrameworks.  Wrapper client runs in it's own thread, server allows multiple threads.  Server has configurable pool threads (operate on server in/out) and worker threads (handle the of callback side work).  


Documentation
* Example client, server, and client-server


************************************************
 SETUP 
************************************************
Hardware Requirements:
* Current inluded libraries (boost, websocketpp) are only included for OS X 32bit.
* Win dll's will be included in the near future.
* Mobile support will be developed long term

Dependencies:
* Boost 1.50.0.0
* websocketpp

Installation
* Download Boost 1.50.00 and place the headers in ofxWebsocketpp/lib/boost/include/ .  Example header path is ofxWebsocketpp/libs/boost/include/boost/version.hpp .  If you already have Boost installed adjust the "User Header Search Paths" to reflect this
* Checkout the websocketpp submodule

Compilation
* Start with the base examples.  If you chose to start from scratch you will need to
  - Add libraries into your new XCode project
  - Add appropriate ofxWebsocketpp header/src to project 
  - Add header paths for Boost and websocketpp to project.  "User Header Search Paths" has these two paths.

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








ofxWebsocketpp
==============

websocketpp wrapper for OpenFrameworks.  

Server supports multithreaded workers.
Client launches in a single thread.
Both client and server are decoupled from ofx loop.  Threaded callbacks to ofEvents, so protect your data structures.

Both a client and server example is included.

You should be able to drag this into the addons folder of ofX, add boost headers, and be good.

websocketpp (https://github.com/zaphoyd/websocketpp) is included with this release.  It will be moved to a submodule in the near future.


macos boost libraries are compiled.  Headers from boost 1.50.0.0 should be placed in 
lib/boost/include/
example header
ofxWebsocketpp/libs/boost/include/boost/version.hpp
... or if you have boost installed you can change header search path via "User Header Search Paths" and point to a new set of libraries.

1.50.0.0 is avaialble here
http://sourceforge.net/projects/boost/files/boost/1.50.0/

All custom header searches are in the "User Header Search Paths" section of XCode Build Settings
