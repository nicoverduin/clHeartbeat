/**
 * @file clHeartbeat.h
 *
 *  Created on	: 16 aug. 2013
 *  Author		: Nico Verduin
 *	Email		: info@verelec.com
 *  Website		: www.verelec.nl
 *
 * Class for making a simple fading LED and implementing it in a sketch. The class has a default Fading
 * schematic that can be changed at creation form the program. The fader can also be switched on and off
 * at the users request.
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

#ifndef Heartbeat_H_
#define Heartbeat_H_
#include "Arduino.h"
//
// class definition
//
class clHeartbeat
{
public:
  clHeartbeat(uint8_t, unsigned long, uint8_t);
  clHeartbeat(uint8_t, uint8_t *, uint8_t, unsigned long);
  clHeartbeat(uint8_t, unsigned long);
  void Update();
  void Start();
  void Stop();
  void ChangeDuration(unsigned long);
  void ChangeOutputPin(uint8_t);

private:

  //
  // properties
  //
  unsigned long _heartBeatCtr;		// next time something has to happen
  unsigned int _fadeIndex;			// initially start at first entry in table
  unsigned int _tableSize;			// size of the fading table
  unsigned int _heartBeatPin;		// pin that connects to heartbeat
  unsigned long _fadeStepSize;		// time between steps
  byte			*_fadeTable;		// pointer to fading table
  bool			 _direction; 		// initially start with incrementing in the table
  unsigned int	_flash;				// indicates flashing instead of fading
  //
  // methods
  //
  void _start();					//  actually starts the timer
};
#endif /* Heartbeat_H_ */
