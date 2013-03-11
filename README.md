##[Node-LEDS](http://www.quietless.com/kitchen/controlling-24-leds-with-node-js-and-a-raspberry-pi/)

This was a quick project to see how difficult it would be to control an Arduino microcontroller over a local network with a Raspberry PI.

To build the project you'll need to setup Node.js. [ideally on a PI if you want to build the project to spec.](http://www.quietless.com/kitchen/how-to-setup-node-js-on-a-raspberry-pi/)

Materials used in this project:

 * [Raspberry PI Model B](http://www.raspberrypi.org/)
 * [Arduino Leonardo](https://www.sparkfun.com/products/11286)
 * [2x 400 tie pt Breadboards](https://www.sparkfun.com/products/9567)
 * [1x Full Length Breadboard](https://www.sparkfun.com/products/112)
 * [4x74HC595 Shift Registers](https://www.sparkfun.com/products/733)
 * [7-Segment Display - 4-Digit](https://www.sparkfun.com/products/9481)
 * [24 Leds](http://www.amazon.com/microtivity-IL188-Assorted-Resistors-Colors/dp/B0060FGA8A)
 * [Bunch of Jumper Wires](http://www.amazon.com/Breadboard-jumper-wire-75pcs-pack/dp/B0040DEI9M)

Installation:

 1. [Follow the schematic to wire everything up](http://quietless.com/docs/node-leds/node-leds.pdf)
 2. Flash the sketch at /arduino/node-led/node-led.ino onto your Arduino
 3. Connect the Arduino to your PI
 4. Fire up the Node server by running the app via > node app
 5. Point a web browser at the IP address of the PI e.g. 192.168.2.1:8080

Any questions, comments, suggestions open an issue or [post a comment on my blog.](http://www.quietless.com/kitchen/controlling-24-leds-with-node-js-and-a-raspberry-pi/)


![Node-LEDS-schematic](http://quietless.com/docs/node-leds/node-leds.png "Node-LEDS-schematic")