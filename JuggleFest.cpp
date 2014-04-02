//
//  JuggleFest.cpp
//  JuggelFest
//
//  Created by Daniel Morton on 3/30/14.
//  Copyright (c) 2014 dan. All rights reserved.
//

#include "JuggleFest.h"

/*
 * Initializer for JuggleFest
 * @param data to process for circuits and Jugglers...
 */
JuggleFest::JuggleFest(std::string data)
{
	//we must have some data to continue
    if (data.empty())
        throw std::invalid_argument( "Input data cannot be empty." );
    
    //lets find any circuit definitions
    std::regex_iterator<std::string::iterator> Cit (data.begin(), data.end(), JuggleRegex::circuitRegex);
    std::regex_iterator<std::string::iterator> Cend;
    while (Cit != Cend)
    {
    	//Our regular expression for circuits should find 8 matches, which is the circuit info we need
        if (Cit->size() >= 8)
        {
        	/* get the length of the circuits now so we can add to it */
            unsigned long i = circuits.size();
            circuits.resize(i+1); //make some room
            /* Create a new circuit object */
            JuggleCircuit *newC = new JuggleCircuit();
            /* Initialize it with our data */
            newC->initializeIterator(Cit);
            circuits[i] = newC; //and save it
        }
        ++Cit;//next match set
    }
	//lets find our jugglers
    std::regex_iterator<std::string::iterator> Jit (data.begin(), data.end(), JuggleRegex::jugglerRegex);
    std::regex_iterator<std::string::iterator> Jend;
    while (Jit != Jend)
    {
        if (Jit->size() > 9)//jugglers must have 9 matches from our regular expression
        {
        	/* get the length of the jugglerParticipants now so we can add to it */        
            unsigned long i = jugglers.size();
            jugglers.resize(i+1);//make some room
            /* New juggler */
            JugglerParticipant *newP = new JugglerParticipant();
            newP->initializeIterator(Jit); //initialize it with our iterator
            jugglers[i] = newP;
        }
        ++Jit;
    }
    
}

/**
 * Get Circuit By Name
 * @param the name of the circuit
 * @return the circuit or null
 */
JuggleCircuit *JuggleFest::getCircuitByName(std::string circuitName)
{
    for (int i = 0; i < circuits.size(); ++i) {
        if (circuits[i]->name == circuitName)//is this our circuit in question? if so return it
            return circuits[i];
    }
    return nullptr;//oops we could not find our circuit... :/
}

static JuggleFest *_staticFestival;

/**
 * Shared Fesitival
 *
 * @return shared JuggleFest Object
 */
JuggleFest *JuggleFest::sharedFestival()
{
    if (_staticFestival == nullptr) //make sure we have initialized before returning our shared Festival
        throw std::invalid_argument( "Must call JuggleFest::initSharedFestival() first" );
    return _staticFestival;
}

/**
 * Initialize Shared Festival object
 *
 * @return shared JuggleFest Object
 */
JuggleFest *JuggleFest::initSharedFestival(std::string data)
{
	//initialize our shared festival for access later...
    _staticFestival = new JuggleFest(data);
    return _staticFestival;
}

/**
 * Get the number of jugglers per circuit
 * @return the number of juggers for each circuit
 */
int JuggleFest::jugglersPerCircuit()
{
	//we cannot divide by zero so if we have zero circuits just return 0
    if (this->circuits.size() == 0) return 0;
    return (int)(this->jugglers.size()/this->circuits.size()); //return how many jugglers per circuit
}
