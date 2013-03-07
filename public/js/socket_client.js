

var socket = io.connect('/');
var socket_connected = false;

socket.on('connected-to-server', function (data) {

	var id = Math.floor(Math.random()*9999);
	$('#user-id').html('Connected : <span style="color:blue">'+id+'</span>');
	socket_connected = true;
	socket.emit('connected-client-response', { id:id });

});