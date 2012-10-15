// This is my pseudo code for connection to Agilart web interface.

class AgilartServer( numberOfDigitalPins, numberOfAnalogPins )
// connection to web interface of agileart
{
    int digitalPins = numberOfDigitalPins;
    int analogPins = numberOfAnalogPins;

    boolean setDigitalPinMode( pinNumber, pinMode_ )
    // set digital pin while running program
    // returns True on success, and False on error 
    {
      if ()
        pinMode( pinNumber, pinMode_ ); // allowed pin modes OUTPUT, INPUT, INPUT_PULLUP
        return True
    };
    
}
