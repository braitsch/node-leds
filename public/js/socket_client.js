

var socket = io.connect('/');
var socket_connected = false;

socket.on('connected-to-server', function (data) {

	socket_connected = true;
	socket.emit('connected-client-response', {name:'stephen'});
	
});