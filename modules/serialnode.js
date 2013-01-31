
var serialport = require("serialport");
var arduino;

serialport.list(function (e, ports) {
	ports.forEach(function(port) {
	// find the port the arduino is connected to //
		if (port.manufacturer == 'FTDI'){
			console.log('* attempting to connect to arduino *');
			arduino = new serialport.SerialPort('/dev/tty.usbserial-' + port.serialNumber, { baudrate: 9600, parser: serialport.parsers.readline("\n") });
			arduino.on("open", function () {
				console.log('* connection successful! *');
				arduino.on('data', onDataReceived);
				setInterval(toggleLed, 2000);
			});
		}
	});
});

var state = 0;

var toggleLed = function()
{
	state = state == 0 ? 1 : 0;
	console.log('serial state :: '+state);
	arduino.write(new Buffer([state]));
}

var onDataReceived = function(data)
{
	console.log('data received : ' + data);
	sendToArduino('Hello from Node!');
}

var sendToArduino = function(m)
{
	arduino.write(m, function(e, results) {
		if (e) {
			console.log('error :: ' + err);
		}	else{
			console.log('message successfully sent');
		}
		if (results) console.log('results :: ' + results);
	});
}