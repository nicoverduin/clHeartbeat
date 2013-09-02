clHeartbeat
===========

Class for creating Fading LEDS (on PWM pin) and flashing Leds (on all digital pins).

Constructors:
-------------

clHeartbeat(unsigned int pin, unsigned long halfDuration, uint8_ t flash);

clHeartbeat(unsigned int pin, byte * fadeArray, unsigned int arraySize, unsigned long halfDuration); 

clHeartbeat (uint8_t pin, unsigned long halfDuration); 

Parameters
----------

+ pin = pin number where the PWM signal is to be sent to. REMEMBER the FADING willonly work on a PWM pin.
+ halfDuration  = Duration of one sequence going through fadeArray (you need 2 for up and down)  
+ flash = if 1 will start flashing 
+ fadeArray = Array to series of Bytes with the PWM values to be sent to the LED. Default the class has a builtin version
+ arraySize = number of entries in fadeArray handed over to the class

Methods
-------

Update() = Call this once in the loop to update the flashers and leds. Do this for every instance of clHeartbeat

Start() = start the Fader or Flasher 

Stop() = Stops the Fader or Flasher

ChangeDuration(unsigned long halfDuration) = Changes the duration of the fading cycle 

ChangeOutputPin(unsigned int pin) = Lets the Fader continue on another pin



