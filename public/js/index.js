
$(document).ready(function(){
	
	var activeButton;
	$('#wrapper #modes .button').click(function(e){
	// prevent selecting the same button twice in a row //
		if (e.target != activeButton){
			activeButton = e.target;
			var n = $(e.target).attr('id').substr(-1);
			setAnimationMode(n);
			if (socket && socket_connected){
				socket.emit('animation-selected', { id:n });
			}
		}
	});
	
	$('#wrapper #auto').click(function(e){
		setAutoMode(!autoMode);
		if (socket && socket_connected){
			socket.emit('set-auto-mode', { autoMode:autoMode });
		}
	});
	
	setAutoMode = function(enabled){
		autoMode = enabled;
		if (autoMode){
			$('#wrapper #auto').addClass('btn-success');
		}	else{
			$('#wrapper #auto').removeClass('btn-success');
		}
	}
	
	setAnimationMode = function(n){
		$('#wrapper #modes .button').each(function(i, o){
			if ($(o).attr('id').substr(-1) == n){
				$(o).addClass('btn-warning');
			}	else{
				$(o).removeClass('btn-warning');
			}
		});
	}
	
});