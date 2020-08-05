## wsServer
 C++ Websocket Server based on QtWebsocket API.
### Building steps: 
#### create a building directory for example 'build'
##### `$ mkdir build`
#### CD to the build output directory (KEY STEP)
##### `$ cd build`
#### Call qmake referencing the .pro file
##### `$ qmake ../wsServer.pro`
#### Call make 
##### `$ make`


## Either run the Server in secure mode WSS or normal WS
### To do so, make the changes in the constructor of the Server class by changing the value of the boolean argument
#### constructor `Server server(portNumber,secure);`
## To test connectopn to the server, i provided the client.html(ws) or sslClient.html(wss) 

