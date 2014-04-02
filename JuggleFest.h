//
//  JuggleFest.h
//  JuggelFest
//
//  Created by Daniel Morton on 3/30/14.
//  Copyright (c) 2014 dan. All rights reserved.
//

#ifndef __JuggelFest__JuggleFest__
#define __JuggelFest__JuggleFest__

#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>
#include <regex>
#include <vector>
#include "JuggleCircuit.h"
#include "JugglerParticipant.h"

/* 
 * regular expressions for finding the Circuit info and Juggler info
 */
namespace JuggleRegex
{
    const std::regex circuitRegex(R"(C\s(C\d*)\s(H:(\d*))\s(E:(\d*))\s(P:(\d*)))");
    const std::regex jugglerRegex(R"(J\s(J\d*)\s(H:(\d*))\s(E:(\d*))\s(P:(\d*))\s((C\d*,?)*))");
}

class JuggleFest
{
public:
	//Vector for our circuit we will populate this with our input data
    std::vector<JuggleCircuit*> circuits;
    //Vector for our jugglers, also populated with input data...
    std::vector<JugglerParticipant*> jugglers;
    
	/*
	 * Initializer for JuggleFest
	 * @param data to process for circuits and Jugglers...
	 */
	JuggleFest(std::string data);
	/**
	 * Get Circuit By Name
	 * @param the name of the circuit
	 * @return the circuit or null
	 */
	JuggleCircuit *getCircuitByName(std::string circuitName);
	/**
	 * Get the number of jugglers per circuit
	 * @return the number of juggers for each circuit
	 */
	int jugglersPerCircuit();
	/**
	 * Shared Fesitival
	 *
	 * @return shared JuggleFest Object
	 */
	static JuggleFest *sharedFestival();
	/**
	 * Initialize Shared Festival object
	 *
	 * @return shared JuggleFest Object
	 */
	static JuggleFest *initSharedFestival(std::string data);
};

#endif /* defined(__JuggelFest__JuggleFest__) */
