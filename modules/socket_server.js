
var arduino = require('./serial_node');

exports.init = function(io){
	
	io.set('log level', 1);
	io.sockets.on('connection', function (socket) {
	// tell client they have successfully connected to the server and wait for their response //
		socket.emit('connected-to-server');
	// listen for the client to tell us who they are //
		socket.on('connected-client-response', function(data){
			socket.user = data;
			onUserConnected(socket);
		});
	});
};

var onUserConnected = function(socket)
{
	console.log('user connected :: '+socket.user.name);
	socket.on('button-pressed', function(data){
		arduino.toggleLed(1);
	});
	socket.on('button-released', function(data){
		arduino.toggleLed(0);
	});
}