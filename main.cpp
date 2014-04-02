//
//  main.cpp
//  JuggelFest
//
//  Created by Daniel Morton on 3/30/14.
//  Copyright (c) 2014 dan. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include "JuggleFest.h"
#include "Helpers.h"

/**
 * JugglerComparer
 * @returns a comparison of our jugglerParticipants based on currentCircuitValue
 */
bool JugglerCMP (JugglerParticipant*a, JugglerParticipant*b) {
    return a->currentCircuitValue > b->currentCircuitValue;
}

int main(int argc, const char * argv[])
{
    /* Lets load the input file which contains the Festival Definition */
	const char * file = "input.txt";
	std::string rawContent;
	rawContent = Helpers::get_file_contents(file);

    /* Initialize the shared JuggleFest with our raw circuit definition for later use */
    JuggleFest::initSharedFestival(rawContent);
    /* Grab a pointer to our shared JuggleFest object for ease of use */
	JuggleFest *fest = JuggleFest::sharedFestival();
    
    /* Before we start processing lets get our dot values 
     * This we had to wait till after we were done initializing to do this as the setPreferredCircuit accesses the sharedFestival obj.
     */
    for (auto element : fest->jugglers) {
        //this will calculate the dot products.
        element->setPreferredCircuits(element->preferedCircuits);
    }
    
    /* Will contain the JugglerParticipants and their assigned circuits */
    std::unordered_map<std::string, std::vector<JugglerParticipant*>> results;
    /* JugglerParticipants that need a home... */
    std::vector<JugglerParticipant*> freeJugglers = fest->jugglers;
    std::cout << "Processing jugglers (" << freeJugglers.size() << ")." << std::endl; //Feedback is always good
    /*While their is a jugglerParticipant with out a home we value to continue searching for one */
    while (!freeJugglers.empty())
    {
        JugglerParticipant *juggler = freeJugglers.front(); //pop the juggler off the front of our vector
        freeJugglers.erase(freeJugglers.begin()); //We do not want to accidentally reuse it so erase it from their.
		//For each circuitName & Dotproduct pair lets try to find a home for our current participant
        for (auto el : juggler->circuitValues) 
        {
        	//Does our currently preferred circuit have room for us?
            if (results[el.circuitName].size() >= fest->jugglersPerCircuit())
            {
            	//Sadly it does not, lets see if we can evict the last participant
                JugglerParticipant *lJuggler = results[el.circuitName].back();
                //is the dotProduct for the current circuit higher for us? 
                if (lJuggler->currentCircuitValue < el.dotProduct) 
                {
                    ///our last juggler is not as good as us.. make some room..
                    lJuggler->clearCircuit(); //so we don't have any accidents
                    results[el.circuitName].erase(results[el.circuitName].end()-1); //they can only have one circuit, so remove him for this
                    freeJugglers.push_back(lJuggler); //start searching for a new home.
                }
                else continue; //there is no room on this team... and we are not good enough, try the next one..
            }
            //There is room lets join the team, and update our currentCircuit to the one we are joining.
            juggler->setCircuit(el.circuitName); 
            //add this participant to the current circuits results
            results[el.circuitName].push_back(juggler);
            //and the current circuit results sort by dotProduct, so we always check the lowest
            std::sort(results[el.circuitName].begin(), results[el.circuitName].end(), JugglerCMP);
            break;
        }
    }

	//now that we have our results array, lets convert it into an easy to read string for output
    std::string resultString ("");
    /* used to calculate the name portion of the yodle email. it is the some the int portion of JugglerParticipant's names in circuit C1970 */
    int emailpart(0); 
    
    /* Define what we are iterator through... */
    typedef std::unordered_map<std::string, std::vector<JugglerParticipant*>>::iterator rit_type;
    for(rit_type iterator = results.begin(); iterator != results.end(); iterator++)
    {
        //circuitName = iterator.first, jugglers = iterator.second
        //lets implode the JugglerParticipants as strings
        std::string imploded("");
        for (auto element : iterator->second) {/*for each participants lets do some work*/
			/* juggler participants and their preferred circuits for this current circuit */
            imploded += element->toString() + ", "; 
            if (iterator->first == "C1970") //Work on the emailPart if this is the circuit we are looking for.
                emailpart += element->nameInt();
        }
        imploded=imploded.substr(0, imploded.length()-2);//we want to remove the trailing ', '
        resultString += iterator->first + " " + imploded + "\n";//
    }
    //write our result to out.txt so we can email it easily...
    Helpers::put_file_contents("out.txt", resultString);
    std::cout << "Output saved to out.txt" << std::endl; //tell the world of our accomplishments
    if (emailpart > 0) //if we have email info lets also tell them about that...
        std::cout << "send email to " << emailpart << "@yodle.com" << std::endl;    
    return 0;
}