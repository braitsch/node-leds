
$(document).ready(function(){
	
	$('#my-btn').mousedown(function(){
		if (socket && socket_connected){
			socket.emit('button-pressed');
		}
	})
	
	$(window).mouseup(function(){
		if (socket && socket_connected){
			socket.emit('button-released');
		}
	})

})