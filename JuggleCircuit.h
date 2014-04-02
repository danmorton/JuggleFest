//
//  JuggleCircuit.h
//  JuggelFest
//
//  Created by Daniel Morton on 3/30/14.
//  Copyright (c) 2014 dan. All rights reserved.
//

#ifndef __JuggelFest__JuggleCircuit__
#define __JuggelFest__JuggleCircuit__

#include <iostream>
#include <regex>

class JuggleCircuit
{
public:
    std::string originalDefinition; /* We currently do not need this, but maybe in the future. */
    std::string name;    /* Circuit Name */
    int HValue;          /* Coordination */
    int EValue;          /* Enduranced   */
    int PValue;          /* Pizzazz      */

	
	/**
	 * Generic initializer for our JugglerCircuit
	 */
	JuggleCircuit();
	/**
	 * Intialize the data after it has been processed
	 * @param data to process
	 */
	void initializeIterator(std::regex_iterator<std::string::iterator> it);
	/**
	 * Performs dot product based on H,E,P values.
	 * @return dot product of this with b
	 */
	int dot(JuggleCircuit *b);
};


#endif /* defined(__JuggelFest__JuggleCircuit__) */

