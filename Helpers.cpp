//
//  Helpers.cpp
//  JuggleFest
//
//  Created by Daniel Morton on 3/30/14.
//  Copyright (c) 2014 dan. All rights reserved.
//

#include "Helpers.h"

/*
 * Split a string into the vector based on the delimiter
 * @param string to split
 * @param the delimiter to split by
 * @param the vector reference for our result
 * @return the final vector with all of our stuff
 */
std::vector<std::string> &Helpers::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

/*
 * Split a string into the vector based on the delimiter
 * @param string to split
 * @param the delimiter to split by
 * @return the final vector with all of our stuff
 */
std::vector<std::string> Helpers::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

/*
 * Get File contents 
 * @param the file to get contents from
 * @return the contents of the fill in question
 * @throws error if unable to open file
 */
std::string Helpers::get_file_contents(const char *filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

/*
 * Put File contents 
 * @param the file to put contents into
 * @return the content to put
 */
void Helpers::put_file_contents(const char *filename, std::string content)
{
    std::ofstream ot;
    ot.open (filename);
    ot << content.c_str();
    ot.close();
}


