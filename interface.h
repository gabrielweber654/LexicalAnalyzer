#ifndef INTERFACE_H
#define INTERFACE_H
#include <string>
#include <vector>
#include "lexicalanalyzer.h"

typedef std::vector<std::string> programType;

class Interface
{
private:
    programType programCode;
    void mainmenu();
    void helpfunction();
    void commandhelpfunction();
public:
    void startInterface();
    void readin(LexicalAnalyzer& lexicalAnalysis);
    void showfile(LexicalAnalyzer& lexicalAnalysis);
    void clear(LexicalAnalyzer& lexicalAnalysis);
    void exitprogram();
};

#endif