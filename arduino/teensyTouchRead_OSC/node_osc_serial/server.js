var osc = require('node-osc');
var oscClient;
oscClient = new osc.Client("127.0.0.1", 6010);
const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')

var path = '/dev/cu.usbmodem72904301'
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
  } catch (err) {
    console.log(err);
  }
});

port.write('ROBOT POWER ON\n')
