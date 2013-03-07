
var arduino;
var serialport = require("serialport");
var exec = require('child_process').exec;

var getArduinoPort = function(callback)
{
// attempt to detect an arduino connected to mac osx //
	exec('ls /dev/tty.*', function(error, stdout, stderr){
		var port;
		if (stdout){
			var ports = stdout.split('\n');
			for (var i = ports.length - 1; i >= 0; i--){
				if (ports[i].search('usbmodem') != -1 || ports[i].search('usbserial') != -1) port = ports[i];
			}
		}
		callback(port);
	});
}

getArduinoPort(function(port){
	var arduinoPort;
	if (port){
		arduinoPort = port;
	}	else{
		serialport.list(function (e, ports) {
		// find the port the arduino is connected to //
			ports.forEach(function(port) {
				for (var k in port){
					console.log('prop='+k, 'val='port[k]);
				}
			// raspberry pi //
				if (port.hasOwnProperty('pnpId')){
			// FTDI captures the duemilanove //
			// Arduino captures the leonardo //
					if (port.pnpId.search('FTDI') != -1 || port.pnpId.search('Arduino') != -1) arduinoPort = port.comName;
				}
			});
		});
	}
// attempt connection //
	if (arduinoPort){
		console.log('* attempting to connect to arduino at :', arduinoPort, ' *');
		arduino = new serialport.SerialPort(arduinoPort, { baudrate: 9600, parser: serialport.parsers.readline("\n") });
		arduino.on("open", function () {
			console.log('* connection to arduino successful ! *');
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

exports.writeNumber = function(n)
{
// calling write if an arduino is not connected will crash the server! //
	if (arduino){
	// parse number into multiplier and remainder //
		var m = Math.floor(n/255);
		var r = n%255;
		console.log('sending to arduino ::', n);
		arduino.write(new Buffer([m, r]), function(e, results) {
			if (e) {
				console.log('error :: ' + e);
			}	else{
				console.log('message successfully sent');
			}
		//	if (results) console.log('results :: ' + results);
		});
	}
}