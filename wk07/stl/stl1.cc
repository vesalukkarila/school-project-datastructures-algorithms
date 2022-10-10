#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


/**
 * @brief sort a given vector to an ascending order
 *
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortAsc(std::vector<int>& v)
{

    sort(v.begin(), v.end());

    if (is_sorted(v.begin(), v.end()))
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}

