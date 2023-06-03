# ArduinoDigitalThermostat
This is a proteus project which uses an Arduino Nano as the microcontroller to implement a digital thermostat circuit.

Two sensors DHT11 and DHT22 are shown to work with the code given.

The code is structured into 3 main classes:
* TemperatureController
* TemperatureSensor
* UserInterface

These 3 main classes call other smaller and more spcific classes hidden from the main loop

The UserInterface class is reponsible for both input via buttons and output via display.
Hence is initalizes both the Buttons class and the LCD class to it handles from two main functions read and show.
The read method reads all the inputs and takes appropriate actions
The show method displays the current state of the system on the LCD

The TemperatureSensor class is measuring temperature and acts as a standard template(abstract class) for all the various temperature sensors it can be connected to.
It mainly has read and get methods, where in the read method, the TemperatureSensor reads the temperature from the sensor and the get method fetches the same temperature.

The TemperatureController class is reponsible for maintaining a constant temperature.
It has the update method which will control wheather the fan and heater is on or off based on the desired and measured temperature.


To Simulate:

Please open the project file and import all the source code and click the run button at the bottom of the screen.
The output will be seen in the Schematic Capture tab

Please use the buttons on the left to set the desired temperature

The buttons on DHT22 can be used to simulate actual temperature

The relays at the bottom will switch in accordance with the desired and measured temperature


To use the DHT11 instead of the DHT22, please disconnect the IO2 from DHT22 and connect it to DHT11.
And in the main ino file, include DHT11.hpp instead of DHT22.hpp and initialize tempSensor as DHT11 instead of DHT22.
