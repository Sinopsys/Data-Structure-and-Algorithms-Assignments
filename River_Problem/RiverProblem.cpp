//
// Created by kirill on 11.11.16.
//

#include <fstream>
#include "RiverProblem.h"

/**
 * reads a file input_bridge.txt and assigns std::vector<char> borders
 */
void RiverProblem::read()
{
    std::ifstream my_file(path_in);
    if (!my_file.eof() && !my_file.fail())
    {
        my_file.seekg(0, std::ios_base::end);
        std::streampos fileSize = my_file.tellg();
        borders.resize(fileSize);

        my_file.seekg(0, std::ios_base::beg);
        my_file.read(&borders[0], fileSize);
    }
    my_file.close();
}


/**
 * writes result of the calculation to a file output_bridge.txt
 */
void RiverProblem::write()
{
    std::ofstream my_file(path_out);
    my_file << crossRight1;
    my_file.close();
}

/**
 * calculates the problem, description is in the header file
 */
void RiverProblem::calculate()
{
    bool rightFlag, leftFlag;
    crossRight0 = 1;
    crossLeft0 = 0;
    for (long i = 0; i < borders.size(); ++i)
    {
        rightFlag = (borders[i] == 'R') || (borders[i] == 'B');
        leftFlag = (borders[i] == 'L') || (borders[i] == 'B');
        if ((crossRight0 + (int) rightFlag) < (crossLeft0 + (int) leftFlag + 1))
            crossRight1 = (crossRight0 + (int) rightFlag);
        else
            crossRight1 = (crossLeft0 + (int) leftFlag + 1);
        if ((crossLeft0 + (int) leftFlag) < (crossRight0 + (int) rightFlag + 1))
            crossLeft1 = (crossLeft0 + (int) leftFlag);
        else
            crossLeft1 = (crossRight0 + (int) rightFlag + 1);
        crossRight0 = crossRight1;
        crossLeft0 = crossLeft1;
    }
}

// EOF
