
$(document).ready(function(){
	
	var activeButton;
	$('#wrapper .button').click(function(e){
		if (e.target != activeButton){
			activeButton = e.target;
			$('#wrapper .button').each(function(i, o){
				if(o == e.target){
					$(o).addClass('disabled');
				}	else{
					$(o).removeClass('disabled');
				}
			});
			var n = $(e.target).attr('id').substr(-1);
			if (socket && socket_connected){
				socket.emit('animation-selected', { id:n });
			}
		}
	})

});