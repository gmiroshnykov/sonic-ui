var app = require('express')()
  , server = require('http').createServer(app)
  , io = require('socket.io').listen(server);

server.listen(5000);

app.get('/', function (req, res) {
  res.sendfile(__dirname + '/index.html');
});

var distance = 42;

setInterval(function() {
  io.sockets.emit('distance', distance++);
}, 1000);
