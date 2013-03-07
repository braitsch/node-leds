

var socket = io.connect('/');
var socket_connected = false;
var autoMode;

socket.on('connected-to-server', function (data) {

// update the view based with the current server settings //
	setAutoMode(data.autoModeEnabled);
	setAnimationMode(data.activeAnimation);
	
// generate a random id for this newly connected user //
	var id = Math.floor(Math.random()*9999);
	$('#user-id').html('Connected : <span style="color:blue">'+id+'</span>');
	socket_connected = true;
	socket.emit('connected-client-response', { id:id });

});

socket.on('animation-changed', function (data) {
	setAnimationMode(data.activeAnimation);
});