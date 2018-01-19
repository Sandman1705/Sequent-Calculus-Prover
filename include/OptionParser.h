#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H

#include <string>
#include <vector>

class OptionParser
{
public:
    OptionParser (int &argc, char **argv);
    const std::string& getCmdOption(const std::string &option) const;
    bool cmdOptionExists(const std::string &option) const;
private:
    std::vector <std::string> tokens;
};

#endif // OPTIONPARSER_H
