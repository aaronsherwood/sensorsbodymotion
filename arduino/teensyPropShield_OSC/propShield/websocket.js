//change IP address here
var ipAddress="127.0.0.1"

var socket;

function OnceLoaded() {
  setupSocket();
}

//*****************Connect to Websocket*****************//
function setupSocket() {
  var ipPort = ipAddress + ':8081';
  socket = io.connect(ipPort, {
    port: 8081,
    rememberTransport: false
  });
  socket.on('connect', function() {
    socket.emit('config', {

    });
  });
}

var JSLink = "http://" + ipAddress + ":8081/socket.io/socket.io.js"
var JSElement = document.createElement('script');
JSElement.src = JSLink;
JSElement.onload = OnceLoaded;
document.getElementsByTagName('head')[0].appendChild(JSElement);
