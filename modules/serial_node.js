
/*
	Public API
*/

exports.writeNumber = function(n)
{
// parse number into multiplier and remainder //
	var m = Math.floor(n/255);
	var r = n%255;
	var data = [1, m, r];
	console.log('sending to arduino ::', data);
	sendDataToArduino(new Buffer(data));
}

exports.setAnimation = function(n)
{
	var data = [2, n];
	console.log('sending to arduino ::', data);
	sendDataToArduino(new Buffer(data));
}

exports.setAutoMode = function(n)
{
	var data = [3, n];
	console.log('sending to arduino ::', data);
	sendDataToArduino(new Buffer(data));
}

/*
	Private Methods
*/

var arduino;
var socket = require('./socket_server');
var serialport = require('serialport');
var exec = require('child_process').exec;

/*
	Attempt to connect to Arduino
*/

var detectArduinoOnOSX = function()
{
	var port;
	console.log('* attempting to detect arduino on mac osx *');
	exec('ls /dev/tty.*', function(error, stdout, stderr){
		if (stdout){
			var ports = stdout.split('\n');
			for (var i = ports.length - 1; i >= 0; i--){
				if (ports[i].search('usbmodem') != -1 || ports[i].search('usbserial') != -1) port = ports[i];
			}
		}
		if (port){
			attemptConnection(port);
		}	else{
			detectArduinoOnRaspberryPI();
		}
	});
}

var detectArduinoOnRaspberryPI = function()
{
	var port;
	console.log('* attempting to detect arduino on raspberry pi *');
	serialport.list(function (e, ports) {
		ports.forEach(function(obj) {
			if (obj.hasOwnProperty('pnpId')){
		// FTDI captures the duemilanove //
		// Arduino captures the leonardo //
				if (obj.pnpId.search('FTDI') != -1 || obj.pnpId.search('Arduino') != -1) {
					port = obj.comName;
				}
			}
		});
		if (port){
			attemptConnection(port);
		}	else{
			console.log('* failed to find arduino : please check your connections *');
		}
	});
}

var attemptConnection = function(port)
{
	console.log('* attempting to connect to arduino at :', port, ' *');
	arduino = new serialport.SerialPort(port, { baudrate: 9600, parser: serialport.parsers.readline("\n") });
	arduino.on("open", function () {
		console.log('* connection to arduino successful ! *');
		arduino.on('data', function(data){
	// send incoming data from arduino out to the socket server //
			socket.onDataFromArduino(data);
		});
	});
}

var sendDataToArduino = function(buffer)
{
// calling write if an arduino is not connected will crash the server! //
	if (arduino){
		arduino.write(buffer, function(e, results) {
			if (e) {
				console.log('error :: ' + e);
			}	else{
			//	console.log('message successfully sent');
			}
		});
	}
}

detectArduinoOnOSX();
