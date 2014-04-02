//
//  JugglerParticipant.h
//  JuggelFest
//
//  Created by Daniel Morton on 3/30/14.
//  Copyright (c) 2014 dan. All rights reserved.
//
// JugglerParticipant represents an actual juggler at the festival
//

#ifndef __JuggelFest__JugglerParticipant__
#define __JuggelFest__JugglerParticipant__

#include <iostream>
#include <regex>
#include <vector>
#include <unordered_map>
#include "JuggleCircuit.h"

/* Structure to define stored Circuit names and their DotProducts */
struct CircuitDotProductStruct
{
    std::string circuitName; /* Name of current circuit */
    int dotProduct;			 /* Dot product of that circuit and current JugglerParticipant */
    /* Would be used for sorting purposes, but we remembered that preferred circuits are pre-sorted */
    bool operator < (const CircuitDotProductStruct& b) const
    {
        return (dotProduct < b.dotProduct); /* Compare dot products */
    }
};

class JugglerParticipant : public JuggleCircuit
{
public:
	std::string preferedCircuits;  /* Circuits They Prefer*/
    /* Dot product of our H,E,P values and each circuit we prefer */
    std::vector<CircuitDotProductStruct> circuitValues;
    /* The dot product of our H,E,P values and the current circuit we reside */
    int currentCircuitValue;

	/**
	 * Default initialize for JugglerParticipant 
	 */
	JugglerParticipant();

	/**
	 * Initialize the data after it has been processed
	 * override the initializeIterator so we can catch after the data has been validated.
	 * @param data to process
	 */	
    virtual void initializeIterator(std::regex_iterator<std::string::iterator>);
	/**
	 * Set Preferred Circuits
	 * triggers circuits values to be populated with dot product values
	 * @param comma separated string of preferred circuits in preferred order.
	 */    
    void setPreferredCircuits(std::string);
	/**
	 * Name Integer
	 * @return the interger portion of the name
	 */    
    int nameInt();
	/**
	 * Set current circuit
	 * This should be called when we are added to a circuit vector
	 * @param circuit name
	 *
	 */    
    void setCircuit(std::string);
	/**
	 * Resets the current circuit value
	 * For use when we are kicked from a circuit.
	 */    
    void clearCircuit();
	/**
	 *	Value for circuit name
	 * Iterate through our circuits and get the value for the circuit in question
	 * @param circuit name in question
	 * @return matched value of that circuit, 0 if not found.
	 */    
    int valueForCircuitName(std::string);
	/**
	 * To String
	 * Gets a string representation of our circuit, for output purposes.
	 * @return string representation of this object
	 */    
    std::string toString();
};



#endif /* defined(__JuggelFest__JugglerParticipant__) */
