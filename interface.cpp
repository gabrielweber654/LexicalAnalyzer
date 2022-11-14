#include <iostream>
#include "interface.h"
#include "lexicalanalyzer.h"
#include <fstream>
#include <string>
using namespace std;

string input;
string subinput;
string filename;
bool program = true;
int iterate = 0;

void Interface::startInterface() 
{
    cout << "PySub Interpreter 1.0 on Windows (September 2020)\n";
    cout << "Enter program files or read(<filename>.py) at command line interface\n";
    cout << "Type 'help' for more information or 'quit' to exit\n";
    mainmenu();
}

void Interface::mainmenu() 
{
    LexicalAnalyzer lexicalAnalysis;
    while (program == true)
    {
        cout << "\n>>>";
        getline(cin, input);
		if (input[0] == 'h' && input[1] == 'e' && input[2] == 'l' && input[3] == 'p' && input[4] == '(' && input[5] != ')')
		{
			commandhelpfunction();
		}
		else if (input == "help" || input == "help()")
		{
			helpfunction();
		}
		else if (input == "show" || input == "show()")
		{
			showfile(lexicalAnalysis);
		}
        else if (input == "show(tokens)")
		{
            lexicalAnalysis.showAnalyze(iterate, input, programCode);
		}
		else if (input[0] == 'r' && input[1] == 'e' && input[2] == 'a' && input[3] == 'd' && input[4] == '(')
		{
			readin(lexicalAnalysis);
		}
		else if (input == "read" || input == "read()")
		{
			cout << "Please input read function as read(filename.py)\n";
		}
        else if (input == "clear" || input == "clear()")
		{
            clear(lexicalAnalysis);
		}
        else if (input == "quit" || input == "quit()")
		{
            exitprogram();
		}
		else
		{
			cout << "Please input an actual command, type help for a list of commands.\n";
		}
    }
    return;
}

void Interface::helpfunction()
{
	cout << "Welcome to the help utility!\n";
	cout << "* To exit the help menu and return to the interpreter, type 'exit'\n";
	cout << "* To get a list of commands, type 'commands'\n";
	cout << "* To get a description of any command, just type the command at the help> prompt\n";
	while (input != "exit")
	{
		cout << "help> ";
		getline(cin, input);
		if (input == "commands")
		{
			cout << "Below is a list of commands. Enter any command at the prompt to get more help\n\n";
			cout << "clear\thelp\tquit\n";
			cout << "read\tshow\n\n";
			cout << "NOTE: All commands can also be entered as functions:\n\n\n";
			cout << "clear()\thelp()\tquit()\n";
			cout << "read()\tshow()\n\n";
		}
		else if (input == "help" || input == "help()")
		{
			cout << "This command gives information on different commands.\n";
		}
		else if (input == "quit" || input == "quit()")
		{
			cout << "This command exits the command line interpreter.\n";
		}
		else if (input == "read" || input == "read()")
		{
			cout << "This command has to be written in the format of read(<filename>.py) which reads in program \n";
			cout << "lines from the file and stores those lines into program code.\n";
		}
		else if (input == "show" || input == "show()")
		{
			cout << "This command shows the lines of the program that are stored in program data, including the line numbers.\n";
		}
		else if (input == "clear" || input == "clear()")
		{
			cout << "This command clears out any lines that are stored in the program code.\n";
		}
		else if (input == "exit" || input == "exit()")
		{
			break;
		}
	}
	input.clear();
	return;
}
void Interface::commandhelpfunction() 
{
	if (input.size() >= 6)
	{
		for (int i = 5; i != (input.size() - 1); i++)
		{
			subinput += input[i];
		}
		if (subinput == "quit" || subinput == "quit()")
		{
			cout << "This command exits the command line interpreter.\n";
		}
		else if (subinput == "help" || subinput == "help()")
		{
			cout << "This command gives information on different commands.\n";
		}
		else if (subinput == "read" || subinput == "read()")
		{
			cout << "This command has to be written in the format of read(<filename>.py) which reads in program \n";
			cout << "lines from the file and stores those lines into program code.\n";
		}
		else if (subinput == "show" || subinput == "show()")
		{
			cout << "This command shows the lines of the program that are stored in program data, including the line numbers.\n";
		}
		else if (subinput == "clear" || subinput == "clear()")
		{
			cout << "This command clears out any lines that are stored in the program code.\n";
		}
		else if (subinput == "exit" || subinput == "exit()")
		{
			;
		}
	}
	else
	{
		cout << "Error - please enter in help commands as help(<command>)";
	}
	input.clear();
	subinput.clear();
	return;	
}

void Interface::readin(LexicalAnalyzer& lexicalAnalysis)
{
    string temp;
    ifstream file;
	string templine;
    bool validfile = true;
    programCode.clear();
    filename.clear();
	if (input.size() >= 6) 
	{
		for (int i = 5; input[i] != ')'; i++)
		{
			filename += input[i];
		}
		if (filename.substr(filename.find_last_of(".") + 1) == "py")
		{
			file.open(filename);
			if (file.fail())
			{
				validfile = false;
				cout << "Error - file does not exist.\n\n";
			}
			while (!file.eof() && validfile != false)
			{
				getline(file, temp);
				programCode.push_back(temp);
				lexicalAnalysis.analyzefile(filename, input, programCode, iterate);
				iterate++;
			}
		}
		else if (filename.length() == 0)
		{
			cout << "Error - please enter in a file with contents (file is empty)\n\n";
		}
		else
		{
			cout << "Error - please enter file in py format\n";
		}
	}
	else
	{
		cout << "Error - please enter file in py format\n";
	}
	return;
}

void Interface::showfile(LexicalAnalyzer& lexicalAnalysis)
{
    if (filename.length() > 0) 
    {
		for (int i = 0; i < programCode.size(); i++)
			cout << "[" << i << "]  " << programCode.at(i) << "\n";
    }
    else
    {
		cout << "Error - no file found\n";
    }
}

void Interface::clear(LexicalAnalyzer& lexicalAnalysis)
{
	filename.clear();
	programCode.clear();
	iterate = 0;
	lexicalAnalysis.cleartokens();
}

void Interface::exitprogram() 
{
    cout << "\tThanks for using PySub!\n";
    program = false;
    return;
}