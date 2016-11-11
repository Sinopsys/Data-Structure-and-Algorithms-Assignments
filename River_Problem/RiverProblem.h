#ifndef RIVER_PROBLEM_RIVERPROBLEM_H
#define RIVER_PROBLEM_RIVERPROBLEM_H

//
// Created by kirill on 11.11.16.
//

#include <string>
#include <vector>

/**
 * crossRight_i - number of crossed parts to reach point [i] on the right bank
 * crossLeft_i - number of crossed parts to reach point [i] on the left bank
 * At first of course crossRight0 = 1 and crossLeft0 = 0
 * I use the following recursive formula to determine the minimum number of crossings to reach the right bank:
 * crossRight_i = min[(crossRight_{i-1} + rightFlag_i), (crossLeft_{i-1} + leftFlag_i + 1)]
 * where rightFlag_i is 1 when there is a river between i-1-th and i-th place (on the right).
 * Obviously, it is 1 when we see R or B.
 * And leftFlag_i is the same for the left side. Obviously, it is 1 when we see L or B.
 */

class RiverProblem
{
private:
    long crossRight0, crossLeft0, crossRight1, crossLeft1;
    std::string path_in = "input_bridge.txt";
    std::string path_out = "output_bridge.txt";
    std::vector<char> borders;
public:
    void read();

    void write();

    void calculate();
};


#endif //RIVER_PROBLEM_RIVERPROBLEM_H

// EOF
