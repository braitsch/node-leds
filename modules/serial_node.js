
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
			});
		}
	});
});

var onDataReceived = function(data)
{
	console.log('data received : ' + data);
}

exports.toggleLed = function(n)
{
	console.log('sending to arduino ::', n);
	arduino.write(new Buffer([n]), function(e, results) {
		if (e) {
			console.log('error :: ' + err);
		}	else{
			console.log('message successfully sent');
		}
		if (results) console.log('results :: ' + results);
	});
}