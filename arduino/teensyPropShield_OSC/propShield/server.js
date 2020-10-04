var osc = require('node-osc');
var io = require('socket.io')(8081);
var connect = require('connect');
var serveStatic = require('serve-static');
var oscClient;
oscClient = new osc.Client("127.0.0.1", 6010);
const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
var isConnected = false;
var globalSocket;

var path = '/dev/tty.usbmodem72904301'
const port = new SerialPort(path, {
  baudRate: 9600
})

const parser = new Readline({
  delimiter: '\r\n'
})
port.pipe(parser)

parser.on('data', line => {
  try {
    // split the string
    let string = line.split(',');

    // first part of the string is the route: 'ctrl'
    // second part is the name. i.e. "touchRead" or hwoever you named interval
    // the third part is the value
    console.log(string[0] + " " + string[1] + " " + string[2]);

    var msg = [
      string[0],
      {
        type: "string",
        value: string[1]
      },
      {
        type: "float",
        value: parseFloat(string[2]) || 0
      }

    ];
    oscClient.send(msg);
    if (isConnected) {
      globalSocket.emit("message", line);
    }
  } catch (err) {
    console.log(err);
  }
});

port.write('ROBOT POWER ON\n')

var isConnected = false;

io.sockets.on('connection', function(socket) {
  console.log('connection');
  globalSocket = socket;
  socket.on("config", function(obj) {
    isConnected = true;
    socket.emit("message", "connected");

  });
  socket.on("message", function(obj) {
    oscClient.send.apply(oscClient, obj);
    console.log(obj);
  });
  socket.on('disconnect', function() {
    if (isConnected) {
      isConnected = false;
    }
  });
});

connect().use(serveStatic(__dirname)).listen(8000, function() {
  console.log('Server running on 8000...');
});
