#include <iostream>
#include "lexicalanalyzer.h"
#include <string>
#include <fstream>

using namespace std;

void LexicalAnalyzer::analyzefile(string filename, string input, vector<string> programCode, int linenum)
{
    string token;
    string tempstring;
    int charnum = 0;
    tokenLineType linetokens;
    while ((charnum < programCode[linenum].size()))
    {
        if (programCode[linenum].at(charnum) == '=')
        {
            token = programCode[linenum].at(charnum);
            linetokens.push_back(make_pair(token, categoryType::ASSIGNMENT_OP));
        }
        else if (isalpha(programCode[linenum].at(charnum))) 
        {
            int tokentemp = 0;
            tokentemp = charnum;
            while (isalpha(programCode[linenum].at(tokentemp++))) //parsing through
            {
                tempstring = tempstring + programCode[linenum].at(charnum);
                charnum++;
                tokentemp = charnum;
            }
            charnum--;
            tokentemp = charnum;

            if (tempstring == "x") //x is only used as an identifier
            {
                token = programCode[linenum].at(charnum);
                linetokens.push_back(make_pair(token, categoryType::IDENTIFIER));
            }
            else if (tempstring == "print" || tempstring == "if" || tempstring == "elif" || tempstring == "else" || tempstring == "input" || tempstring == "while")
            {
                token = tempstring;
                linetokens.push_back(make_pair(token, categoryType::KEYWORD));
            }
            else if (tempstring == "and" || tempstring == "not" || tempstring == "or")
            {
                token = tempstring;
                linetokens.push_back(make_pair(token, categoryType::LOGICAL_OP));
                tempstring.clear();
            }
            else //catch-all is string literal
            {
                token = tempstring;
                linetokens.push_back(make_pair(token, categoryType::STRING_LIT));
            }
            tempstring.clear();
        }
        else if (programCode[linenum].at(charnum) == '"')
        {
            while (programCode[linenum].at(charnum++) != '"')
            {
                token = token + programCode[linenum].at(charnum);
                charnum++;
            }
            charnum--;
            linetokens.push_back(make_pair(token, categoryType::STRING_LIT));
        }
        else if (isdigit(programCode[linenum].at(charnum))) //if its a digit
        {
            int tokennumtemp = 0;
            tokennumtemp = charnum;
            while (tokennumtemp < programCode[linenum].size() && isdigit(programCode[linenum].at(tokennumtemp++))) //loop to get the whole number
            {
                token = token + programCode[linenum].at(charnum);
                charnum++;
                tokennumtemp = charnum;
            }
            linetokens.push_back(make_pair(token, categoryType::NUMERIC_LIT));
            charnum--;
            tokennumtemp = charnum;
        }
        else if (programCode[linenum].at(charnum) == '+' || programCode[linenum].at(charnum) == '-' || programCode[linenum].at(charnum) == '*' || programCode[linenum].at(charnum) == '/' || programCode[linenum].at(charnum) == '%')
        {
            token = programCode[linenum].at(charnum);
            linetokens.push_back(make_pair(token, categoryType::ARITH_OP));
            charnum++;
        }
        else if (programCode[linenum].at(charnum) == '<' || programCode[linenum].at(charnum) == '>' || programCode[linenum].at(charnum) == '<=' || programCode[linenum].at(charnum) == '>=' || programCode[linenum].at(charnum) == '==' || programCode[linenum].at(charnum) == '!=')
        {
            token = programCode[linenum].at(charnum);
            linetokens.push_back(make_pair(token, categoryType::RELATIONAL_OP));
            charnum++;
        }
        else if (programCode[linenum].at(charnum) == '(')
        {
            token = programCode[linenum].at(charnum);
            linetokens.push_back(make_pair(token, categoryType::LEFT_PAREN));
        }
        else if (programCode[linenum].at(charnum) == ')')
        {
            token = programCode[linenum].at(charnum);
            linetokens.push_back(make_pair(token, categoryType::RIGHT_PAREN));
            charnum++;
        }
        else if (programCode[linenum].at(charnum) == ':')
        {
            token = programCode[linenum].at(charnum);
            linetokens.push_back(make_pair(token, categoryType::COLON));
        }
        else if (programCode[linenum].at(charnum) == ',')
        {
            token = programCode[linenum].at(charnum);
            linetokens.push_back(make_pair(token, categoryType::COMMA));
        }
        else if (programCode[linenum].at(charnum) == '#') //all comments start with #
        {
            while (charnum < programCode[linenum].size())
            {
                token = token + programCode[linenum].at(charnum);
                charnum++;
            }
            linetokens.push_back(make_pair(token, categoryType::COMMENT));
        }
        else if ((programCode[linenum].at(charnum) == '\t') && charnum == 0) //tabs at the start
        {
            token = programCode[linenum].at(charnum);
            linetokens.push_back(make_pair(token, categoryType::INDENT));
        }
        else if (programCode[linenum].at(charnum) == '\n' || programCode[linenum].at(charnum) == ' ')
        {
            ; //IGNORES
        }
        else
        {
            token = programCode[linenum].at(charnum);
            linetokens.push_back(make_pair(token, categoryType::UNKNOWN));
        }
        charnum++;
        token.clear();
    }
    tokenInfo.push_back(linetokens);
}

string LexicalAnalyzer::getCategory(categoryType actualcategory)
{
    switch (actualcategory) //assigns categoryTypes to the cout'ed category
    {
    case categoryType::KEYWORD:
        return "KEYWORD";
        break;
    case categoryType::IDENTIFIER:
        return "IDENTIFIER";
        break;
    case categoryType::STRING_LIT:
        return "STRING LITERAL";
        break;
    case categoryType::NUMERIC_LIT:
        return "NUMERIC LITERAL";
        break;
    case categoryType::ASSIGNMENT_OP:
        return "ASSIGNMENT OPERATOR";
        break;
    case categoryType::ARITH_OP:
        return "ARITHMETIC OPERATOR";
        break;
    case categoryType::LOGICAL_OP:
        return "LOGICAL OPERATOR";
        break;
    case categoryType::RELATIONAL_OP:
        return "RELATIONAL OPERATOR";
        break;
    case categoryType::LEFT_PAREN:
        return "LEFT PARENTHESIS";
        break;
    case categoryType::RIGHT_PAREN:
        return "RIGHT PARENTHESIS";
        break;
    case categoryType::COLON:
        return "COLON";
        break;
    case categoryType::COMMA:
        return "COMMA";
        break;
    case categoryType::COMMENT:
        return "COMMENT";
        break;
    case categoryType::INDENT:
        return "INDENT";
        break;
    case categoryType::UNKNOWN:
        return "UNKNOWN";
        break;
    default:
        return "UNKNOWN";
    }
}

void LexicalAnalyzer::showAnalyze(int linenum, string input, vector<string> programCode)
{
    cout << "**********TOKEN INFORMATION**********";
    for (int l = 0; l < tokenInfo.size(); l++) //incrementing by line
    {
    cout << "---------------------------------";
        cout << "\nLine #" << l << ":\n";  //displaying line num
        for (int c = 0; c < tokenInfo[l].size(); c++)
        {
            cout << "TOKEN #" << c << ": "; //displaying token num
            cout << "- " << tokenInfo[l][c].first; //first part of the token
            cout << " - " << getCategory(tokenInfo[(l)][c].second) << endl; //second part
        }
    }
    cout << "\n\n";
}

void LexicalAnalyzer::cleartokens()
{
    tokenInfo.clear();
}

