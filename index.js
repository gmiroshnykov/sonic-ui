var app = require('express')()
  , server = require('http').createServer(app)
  , io = require('socket.io').listen(server);

server.listen(5000);

app.get('/', function (req, res) {
  res.sendfile(__dirname + '/index.html');
});

var SerialPort = require("serialport").SerialPort;
var serialPort = new SerialPort("/dev/tty.usbmodem621", {
  baudrate: 9600
});
var split = require('split');
serialPort.pipe(split())
    .on('data', function (line) {
      //each chunk now is a seperate line!
      console.log(line);
      io.sockets.emit('distance', line);
    });
