let serialport = require('serialport');

function listPorts() {
 serialport.list().then(
  ports => {
   ports.forEach(port => {
    console.log(`${port.comName}\t${port.pnpId || ''}\t${port.manufacturer || ''}`)
   })
  },
  err => {
   console.error('Error listing ports', err)
  }
 )
}

listPorts();
