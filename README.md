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
