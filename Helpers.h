//
//  Helpers.h
//  JuggleFest
//
//  Created by Daniel Morton on 3/30/14.
//  Copyright (c) 2014 dan. All rights reserved.
//

#ifndef __JuggleFest__Helpers__
#define __JuggleFest__Helpers__

#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>


/*
 * Helper Class
 * because everyone needs a little help sometimes...
 * just a bunch of function without a home
 */
class Helpers
{
public:
	/*
	 * Split a string into the vector based on the delimiter
	 * @param string to split
	 * @param the delimiter to split by
	 * @param the vector reference for our result
	 * @return the final vector with all of our stuff
	 */
	static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
	/*
	 * Split a string into the vector based on the delimiter
	 * @param string to split
	 * @param the delimiter to split by
	 * @return the final vector with all of our stuff
	 */
	static std::vector<std::string> split(const std::string &s, char delim);
	/*
	 * Get File contents 
	 * @param the file to get contents from
	 * @return the contents of the fill in question
	 * @throws error if unable to open file
	 */
	static std::string get_file_contents(const char *filename);
	/*
	 * Put File contents 
	 * @param the file to put contents into
	 * @return the content to put
	 */
	static void put_file_contents(const char *filename, std::string content);
};


#endif /* defined(__JuggleFest__Helpers__) */


