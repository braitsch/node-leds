
var serialport = require("serialport");
var arduino;

serialport.list(function (e, ports) {
	var arduinoPort;
	// find the port the arduino is connected to //
	ports.forEach(function(port) {
	// macbookpro //
		if (port.manufacturer == 'FTDI'){
			arduinoPort = '/dev/tty.usbserial-' + port.serialNumber;
	// raspberry pi //
		}	else if (port.pnpId.search('FTDI') != -1){
			arduinoPort = port.comName;
		}
	});
	if (arduinoPort){
		console.log('attempting to connect to :', arduinoPort);
		arduino = new serialport.SerialPort(arduinoPort, { baudrate: 9600, parser: serialport.parsers.readline("\n") });
		arduino.on("open", function () {
			console.log('* connection successful! *');
			arduino.on('data', onDataReceived);
		});
	}	else{
		console.log('* failed to find arduino : please check your connections *');
	}
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