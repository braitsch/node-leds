
var sockets;
var arduino = require('./serial_node');
var activeUser;
var activeAnimation = 1;
var autoModeEnabled = true;

/*
	TODO - need to store the current animation & autoMode setting on the server
*/

exports.init = function(io){
	
	sockets = io.sockets;
	io.set('log level', 1);
	sockets.on('connection', function (socket) {
	// only allow the most recent connected user to control the arduino //
		activeUser = socket;
	// tell client they have successfully connected to the server and wait for their response //
		socket.emit('connected-to-server', {
			activeAnimation:activeAnimation,
			autoModeEnabled:autoModeEnabled
		});
	// listen for the client to tell us who they are //
		socket.on('connected-client-response', function(data){
			socket.user = data;
			onUserConnected(socket);
		});
	});
};

exports.onDataFromArduino = function(data){
	console.log('onDataFromArduino', data);
	if (data.search('MODE') != -1){
	// get the fifth character off the string to set the mode //
		activeAnimation = data.substr(4, 1);
	// and updated active clients with the new animation change //
		sockets.emit('animation-changed', {
			activeAnimation:activeAnimation
		});
	}
};

var onUserConnected = function(socket)
{
	arduino.writeNumber(socket.user.id);
	socket.on('animation-selected', function(data){
	// only allow the most recent connected user to control the arduino //
		if (socket === activeUser) {
			activeAnimation = data.id;
			arduino.setAnimation(activeAnimation);
		}
	});
	socket.on('set-auto-mode', function(data){
	// only allow the most recent connected user to control the arduino //
		if (socket === activeUser) {
			autoModeEnabled = data.autoMode;
			arduino.setAutoMode(autoModeEnabled);
		}
	});
}