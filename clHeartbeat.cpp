/**
 * @file clHeartbeat.cpp
 *
 *  Created on	: 16 aug. 2013
 *  Author		: Nico Verduin
 *	Email		: info@verelec.com
 *  Website		: www.verelec.nl
 *
 * Class for making a simple fading LED and implementing it in a sketch. The class has a default Fading
 * schemae that can be changed at creation time from the program itself. The fader can also be switched on and off
 * at the users request or the output pin may be changed and even the cycle time.
 * The output is a PWM signal generated based on the values in a byte array.
 *
 * This class can be implemented multiple times in a sketch.
 *
 * Revision Control
 *
 * Latest Revsion
 * ____________________
 *
 * Revision	: $Revision$
 * Date		: $Date$
 * Author	: $Author$
 *
 */

 // Do not remove the include below
#include "clHeartbeat.h"
#define FLASH 1
//
// implemented methods
//
/**
 * @name clHeartbeat(unsigned int pin, unsigned long halfDuration, uint8_t flash)
 * @param pin			pin number where the PWM signal is to be sent to
 * @param halfDuration	Duration of one sequence going through fadeArray (you need 2 for up and down)
 * @param flash			if 1 wil start flashing
 *
 * This is the constructor where all controllable parameters may be modified
 */
clHeartbeat::clHeartbeat(const uint8_t pin, const unsigned long halfDuration, const uint8_t flash) {
	_fadeStepSize 	= halfDuration;					// duration between indexed steps
	_heartBeatPin	= pin;							// output pin
	_flash 			= 1;							// flashing instead of fading
	_start();
}

/**
 * @name clHeartbeat(unsigned int pin, byte * fadeArray, unsigned int arraySize, unsigned long halfDuration)
 * @param pin			pin number where the PWM signal is to be sent to
 * @param fadeArray		pointer to a byte array containing the PWM parameters
 * @param arraySize 	Size of the fadeArray in bytes
 * @param halfDuration	Duration of one sequence going through fadeArray (you need 2 for up and down)
 *
 * This is the constructor where all controllable parameters may be modified
 */
clHeartbeat::clHeartbeat(uint8_t pin, uint8_t * fadeArray, uint8_t arraySize, unsigned long halfDuration){
	//
	// setup the heartbeat
	//
	_tableSize 		= arraySize;					// size of the passed array
	_fadeStepSize 	= halfDuration / _tableSize;	// duration between indexed steps
	_heartBeatPin	= pin;							// output pin
	_fadeTable		= fadeArray;					// pointer to array with PWM values
	_flash			= 0;							// fading not flashing
	_start();
}

/**
 * @name clHeartbeat(unsigned int pin, unsigned long halfDuration)
 * @param pin			pin number where the PWM signal is to be sent to
 * @param halfDuration	Duration of one sequence going through fadeArray (you need 2 for up and down)
 *
 * This is the constructor where only the pin number and duration can be modified. The array is a default (pretty good one). By
 * making it static, if more heartbeat classes are defined, they will use the same table unless different is specified
 */
clHeartbeat::clHeartbeat(uint8_t pin, unsigned long halfDuration){
	//
	// default array with PWM values
	//
	static uint8_t defaultFadeTable[] = { 1	,6	,12	,23	,34	,45	,55	,65	,75	,85	,
										 94	,103,112,120,129,137,145,153,160,167,
										 174,181,187,193,199,205,210,215,220,225,
										 229,233,237,241,242,243,244,245,246,247,
										 248,249,250,251,252,253,254
										};
	//
	// setup the heartbeat
	//
	_tableSize 		= sizeof(defaultFadeTable);		// size of default array above
	_fadeStepSize 	= halfDuration / _tableSize;	// duration between indexed steps
	_heartBeatPin	= pin;							// output pin
	_fadeTable		= defaultFadeTable;				// points to the default array above
	_flash			= 0;							// fading not flashing
	_start();
}

/**
 * @name Stop()
 * this method stops the heartbeat. The used Pin is free for other use.
 */
void clHeartbeat::Stop(){
	//
	// just rest the heartBeatCtr
	//
	_heartBeatCtr = 0;
	//
	// switch the LED off
	//
	digitalWrite(_heartBeatPin, LOW);
}

/**
 * @name Start()
 * this method starts the heartbeat. The used Pin is free for other use.
 */
void clHeartbeat::Start(){
	//
	// if the user has used this pin or other use, we need to redefine this pin.
	//
	_start();
}
/**
 * @name ChangeDuration(unsigned long halfDuration)
 * @param halfDuration	Duration of one sequence going through fadeArray (you need 2 for up and down)
 *
 * Changes the duration between steps
 */
void clHeartbeat::ChangeDuration(unsigned long halfDuration){
	//
	// change the time between steps
	//
	_fadeStepSize 	= halfDuration / _tableSize;	// duration between indexed steps

}
/**
 * @name ChangeOutputPin(unsigned int pin)
 * @param pin	Pin to set new output on)
 *
 * Changes the output pin
 */
void clHeartbeat::ChangeOutputPin(uint8_t pin) {
	_heartBeatPin = pin;
	_start();
}

/**
 * @name Update()
 * Lets the LED fade in and Fade out through time set parameters
 */
void clHeartbeat::Update(){
	if (_flash == FLASH) {
		//
		// flashing instead of fading
		//
		if (millis() > _heartBeatCtr && _heartBeatCtr != 0L) {
			//
			// invert output pin
			//
			digitalWrite(_heartBeatPin, !digitalRead(_heartBeatPin));
			//
			// set ready for next time
			//
			_heartBeatCtr = millis() + _fadeStepSize;
		}
	} else {
		//
		// test if we need to update. Only if active. If heartBeatCtr == 0 it is switched off
		//
		if (millis() > _heartBeatCtr && _heartBeatCtr != 0L) {
			//
			// Now send the fade value to the LED PWM
			//
			analogWrite(_heartBeatPin,_fadeTable[_fadeIndex]);

			//
			// yes so first determine the direction in the fading table
			//
			if (_direction) {
				//
				// is true so increment in the fading table
				//
				_fadeIndex++;
				//
				// check if we are at the max of the table index
				//
				if (_fadeIndex == (_tableSize - 1)) {
					//
					// we will go down next time
					//
					_direction = false;
				}
			} else {
				//
				// is false so we move to the next lower indexed entry in the fade table
				//
				_fadeIndex--;
				//
				// Check if we are at the lowest entry
				//
				if (_fadeIndex == 0) {
					//
					// Next time we will increment the table index
					//
					_direction = true;
				}
			}
			//
			// set the millis counter ready for the next time
			//
			_heartBeatCtr = millis() + _fadeStepSize;
		}
	}
}
//
// private methods
//
/**
 * @name _Start()
 * this method starts the heartbeat. The used Pin is free for other use.
 */
void clHeartbeat::_start(){
	//
	// if the user has used this pin or other use, we need to redefine this pin.
	//
	pinMode(_heartBeatPin, OUTPUT);
	_fadeIndex 		= 0;							// we start at index 0
	_direction		= true;							// we start upwards
	//
	// start the millisecond counter
	//
	_heartBeatCtr = millis() + _fadeStepSize;
}

