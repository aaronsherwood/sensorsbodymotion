//change IP address here
var ipAddress="127.0.0.1"

var x = [];
x.push({
	type: 'float',
	value: 0
})
var y = [];
y.push({
	type: 'float',
	value: 0
})
var socket;

//*****************Connect to Websocket*****************//
function setupOsc(oscPortIn, oscPortOut) {
  var ipPort = ipAddress + ':8081';
  socket = io.connect(ipPort, {
    port: 8081,
    rememberTransport: false
  });
  socket.on('connect', function() {
    socket.emit('config', {
      server: {
        port: oscPortIn,
        host: ipAddress
      },
      client: {
        port: oscPortOut,
        host: ipAddress
      }
    });
  });
  socket.on('message', function(msg) {
    if (msg[0] == '#bundle') {
      for (var i = 2; i < msg.length; i++) {
        receiveOsc(msg[i][0], msg[i].splice(1));
      }
    } else {
      receiveOsc(msg[0], msg.splice(1));
    }
  });
}

function receiveOsc(address, value) {
  console.log("received OSC: " + address + ", " + value);
}

var JSLink = "http://" + ipAddress + ":8081/socket.io/socket.io.js"
var JSElement = document.createElement('script');
JSElement.src = JSLink;
JSElement.onload = OnceLoaded;
document.getElementsByTagName('head')[0].appendChild(JSElement);

function OnceLoaded() {
  setupOsc(6449, 6448);
}
