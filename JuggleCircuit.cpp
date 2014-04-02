//
//  JuggleCircuit.cpp
//  JuggelFest
//
//  Created by Daniel Morton on 3/30/14.
//  Copyright (c) 2014 dan. All rights reserved.
//

#include "JuggleCircuit.h"

/**
 * Generic initializer for our JugglerCircuit
 */
JuggleCircuit::JuggleCircuit(){}

/**
 * Intialize the data after it has been processed
 * @param data to process
 */
void JuggleCircuit::initializeIterator(std::regex_iterator<std::string::iterator> it)
{
	//validate that we have at least 8 matches in this iterator...
    if (it->size()<8)
        throw std::invalid_argument( "Invalid iterator size." );
    
    //based on the regular expression populate our data fields with the correct values.
    this->originalDefinition = it->str(0);
    this->name = it->str(1);
    this->HValue = atoi(it->str(3).c_str());
    this->EValue = atoi(it->str(5).c_str());
    this->PValue = atoi(it->str(7).c_str());
    
}

/**
 * Performs dot product based on H,E,P values.
 * @return dot product of this with b
 */
int JuggleCircuit::dot(JuggleCircuit *b)
{
	//return the H,E,P dot product with other JugglerCircuit (will actually be a JugglerParticipant)
    return this->HValue * b->HValue + this->EValue * b->EValue + this->PValue * b->PValue;
}