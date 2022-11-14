#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H
#include <string>
#include <vector>

enum class categoryType
{
    KEYWORD,
    IDENTIFIER,
    STRING_LIT,
    NUMERIC_LIT,
    ASSIGNMENT_OP,
    ARITH_OP,
    LOGICAL_OP,
    RELATIONAL_OP,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COMMA,
    COMMENT,
    INDENT,
    UNKNOWN
};

typedef std::vector<std::vector<std::pair<std::string, categoryType>>> tokenType;
typedef std::vector<std::pair<std::string, categoryType>> tokenLineType;
typedef std::pair<std::string, categoryType> pairType;

class LexicalAnalyzer
{
private:
public:
    tokenType tokenInfo;
    void analyzefile(std::string, std::string, std::vector<std::string>, int);
    void showAnalyze(int, std::string, std::vector<std::string>);
    void cleartokens();
    std::string getCategory(categoryType);
};


#endif