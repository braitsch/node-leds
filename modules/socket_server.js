
var arduino = require('./serial_node');
var activeUser;
var activeAnimation;

/*
	TODO - need to store the current animation & autoMode setting on the server
*/

exports.init = function(io){
	
	io.set('log level', 1);
	io.sockets.on('connection', function (socket) {
	// only allow the most recent connected user to control the arduino //
		activeUser = socket;
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
	arduino.writeNumber(socket.user.id);
	socket.on('animation-selected', function(data){
	// only allow the most recent connected user to control the arduino //
		if (socket === activeUser) arduino.setAnimation(data.id);
	});
}