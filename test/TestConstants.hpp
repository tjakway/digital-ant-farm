#ifndef ANTF_TESTCONSTANTS_H
#define ANTF_TESTCONSTANTS_H

#include <string>

/**
 * use static constants instead of preprocessor defines because there's a good chance of these names colliding with macros defined in other libraries
 */
namespace jakway_antf
{
class TestConstants
{
private:
    static const std::string RES_DIR;
public:
    static const std::string ONE_4X4_CSV,
                             NO_BLANKS,
                             ONLY_STRINGS,
                             DIAG_STRINGS;
};

}
#endif
