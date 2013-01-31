
$(document).ready(function(){
	
	$('#my-btn').mousedown(function(){
		console.log('button down');
	})
	
	$(this).mouseup(function(){
		console.log('button up');
	})

})