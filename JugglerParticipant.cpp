//
//  JugglerParticipant.cpp
//  JuggelFest
//
//  Created by Daniel Morton on 3/30/14.
//  Copyright (c) 2014 dan. All rights reserved.
//

#include "JugglerParticipant.h"
#include "JuggleFest.h"
#include "Helpers.h"

/**
 * Default initialize for JugglerParticipant 
 */
JugglerParticipant::JugglerParticipant() {}

/**
 * Set Preferred Circuits
 * triggers circuits values to be populated with dot product values
 * @param comma separated string of preferred circuits in preferred order.
 */
void JugglerParticipant::setPreferredCircuits(std::string preferred)
{
	//save the preferredCircuits string we do not actually need it right now..
    this->preferedCircuits = preferred;
    
    //split our preffered circuits into a vector, so we can get their dot products
    std::vector<std::string> elems;
    elems = Helpers::split(preferred, ',');
    
    
    JuggleFest *festival = JuggleFest::sharedFestival();//pointer to shared JuggleFest object.
    //resize the vector to hold our preferred circuits
    this->circuitValues.resize(elems.size());
    for (int i = 0; i<elems.size(); ++i) {
        JuggleCircuit *c = festival->getCircuitByName(elems[i]);//our currently preferred circuit
        int dotprod = c->dot(this);//the dot product of our HEP values with the Circuit
        this->circuitValues[i] = (CircuitDotProductStruct){c->name, dotprod};//save that info in our circuitValue array for later use
    }
}

/**
 * Initialize the data after it has been processed
 * override the initializeIterator so we can catch after the data has been validated.
 * @param data to process
 */
void JugglerParticipant::initializeIterator(std::regex_iterator<std::string::iterator> it)
{
	//initialize superclass first, this makes sure variables like HEP get populated.
    JuggleCircuit::initializeIterator(it);
    if (it->size()<9)//are we actually valid for this context?
        throw std::invalid_argument( "Invalid iterator size." );
    
	//for now store the preferred circuit string, we will have to process it later.
    this->preferedCircuits = it->str(8);    
}

/**
 * Name Integer
 * @return the interger portion of the name
 */
int JugglerParticipant::nameInt()
{
    return atoi(this->name.substr(1).c_str());//get the integer portion of our name string, (i.e. J71 -> 71)
}

/**
 * Set current circuit
 * This should be called when we are added to a circuit vector
 * @param circuit name
 *
 */
void JugglerParticipant::setCircuit(std::string name)
{
    this->currentCircuitValue = this->valueForCircuitName(name); //get our dotproduct with said circuit and store it for easy access.
}

/**
 * Resets the current circuit value
 * For use when we are kicked from a circuit.
 */
void JugglerParticipant::clearCircuit()
{
    this->currentCircuitValue = 0;
}

/**
 *	Value for circuit name
 * Iterate through our circuits and get the value for the circuit in question
 * @param circuit name in question
 * @return matched value of that circuit, 0 if not found.
 */
int JugglerParticipant::valueForCircuitName(std::string name)
{
    for (auto el : this->circuitValues)
    {
        if (el.circuitName == name) //if this is the circuit we are looking for lets return the value
            return el.dotProduct;
    }
    return 0;
}

/**
 * To String
 * Gets a string representation of our circuit, for output purposes.
 * @return string representation of this object
 */
std::string JugglerParticipant::toString()
{
	//init r with our name.
    std::string r(this->name);
    for (auto el : this->circuitValues) {
        //Add each circuit and its dot product values to the resultant string
        r += " " + el.circuitName + ":" + std::to_string(el.dotProduct);
    }
    return r;
}
