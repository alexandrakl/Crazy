// Joseph Gunderson & Alexandra Klimenko
// Homework 3
// Completed 06.Feb.2016

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using std::cout; using std::endl; using std::string; using std::ifstream; 
using std::cin; using std::setw;

void interactive();
void display();
void read(string fileIn, char eORc);
void stringParser(string code);
void execute(char command);
void cppParser(string code);
void toCPP(char command);

const int size = 1000; // needs to be const in order to pass into array
int tape[size] = {0};  // create a read/write tape and initializes all to 0
int* dp = tape; // initializes pointer to first position in array
string input = ""; // copies input for tracking position of input commands
int stringPtr = 0; // corresponding pointer
int tabCounter = 1; // keeps track out output format for translation to c++

int main(int argc, char** argv)
{
	cout << endl; // formatting preference
	
	// if user passes no command line arguments -> enter interactive mode
	if ( !(argv[1]) )
	{
		interactive();
	}
	
	// else loop through command line input
	for(int i=1; i<argc; ++i)
	{	
		string s = argv[i];
		char c = s.at(1);
		
		// if inputing a file to read -> pass in file
		if( s.at(0)=='-' && (c=='e' || c=='c') )
		{
			read( argv[i+1], c );
			break; // no need to evaluate remaining command line arguments
		}
		// else evaluate input (mainly for debugging)
		else{
			stringParser(s);
		}
	}
	
	
	
	cout << endl; // formatting preference
	return 0;
}



// interactive display
void display()
{
	// so display of memory 'tape' wraps around
	if( dp < tape )
	{
		dp = (tape + 999);
	}
	if( dp > (tape + 999) )
	{
		dp = tape;
	}
	
	// initialize scope of display
	int index = dp-tape;
	int end = 9;
	int begin = 0;
	int x = index;
	
	// if index enters end of memory 'tape'
	// update scope of display so visual-point traces end of display
	if( index > 995 )
	{
		begin = 991;
		end = 1000;
		x = index-991;
	}
	
	// if index greater or equal to middle of display
	// update scope of display so visual-pointer stays in middle of display
	else if( index >=4 )
	{
		begin = index-4;
		end = index+5;
		x = 4;
	}
	
	
	// index display
	cout << "index:      ";
	for(int i=begin; i<end; ++i)
	{
		cout << " |" << setw(4) << i << setw(2) << "|";
	} 
	cout << "\n" << endl;
	
	// char display
	cout << "char value: ";
	int value = 0;
	for(int i=begin; i<end; ++i)
	{
		value = tape[i];
		
		// null indicator
		if(value == 0)
		{
			cout << setw(6) << "/0" << setw(2) << "";
		}
		// no visual ascii 'char' representation
		else if( (value < 32 && value > 0) || value == 127 )
		{
			cout << setw(6) << (char)128 << setw(2) << "";
		}
		// ascii char equivalent
		else
		{
			cout << setw(6) << (char)value << setw(2) << "";
		}
	} 
	cout << "\n" << endl;
	
	// int display
	cout << "int value:";
	for(int i=begin; i<end; ++i)
	{
		cout << setw(8) << tape[i];
	} 
	cout << "\n" << endl;
	
	// pointer display
	cout << "data pointer:";
	cout << setw(5+(8*x)) << "||" << endl;
	
	// size of screen for update
	for(int i=0; i<15; ++i)
	{
		cout << endl;
	}
}


// enter INTERACTIVE mode
void interactive()
{
	string command;
	bool exit = false;
	
	while( !exit )
	{

		display();
		
		cin >> command;
		cout << endl; // format preference
		
		// reinitialize global variables
		input = command;
		stringPtr = 0;
		
		if (command == "exit")
		{
			exit = true;
		}
		else{
			stringParser(command);
		}
		
		cout << endl; // format preference
	}
}


// reads contents of a file into a string value
void read(string fileIn, char eORc)
{
	ifstream fin(fileIn.c_str()); 	// opens file to read from
	
	if ( fin.fail() )
	{
		cout << "Invalid file: " << fileIn << endl;
	}
	
	// reads input commands from a file
	string s; 		
	while(getline(fin,s)) 	
	{	
		if( eORc == 'c' )
		{
			cppParser(s); // passes into c++ translator helper function 
		}
		else{
			stringParser(s); // passes into string parser
		}
	}
}


// loops through a string and passes each character
void stringParser(string code)
{	
	input = code; // saves string of commands into global variable
	
	// breaks each character of string into seperate commands
	// loops until String Pointer reaches end of input length
	while(stringPtr != code.length())
	{
		execute(code.at(stringPtr));
		++stringPtr;
	}
}


// meat & potatoes
void execute(char command)
{	
	int counter = 0;
	
	switch(command)
	{	
		case '+':
			++(*dp);
			break;
		case '-':
			--(*dp);
			break;
		case '>':
			++dp;
			break;
		case '<':
			--dp;
			break;
		case ':':
			cout << *dp;
			break;
		case '.':
			cout << static_cast<char>(*dp);
			break;
		case '{':
			// if value pointed to by dp is zero
			if(*dp==0)
			{
				// jump to corresponding '}'
				for(int i=stringPtr; i<input.length(); ++i)
				{
					if(input.at(i)=='{')
					{
						++counter;
					}
					if(input.at(i)=='}')
					{
						--counter;
					}
					if(counter == 0)
					{ 
						stringPtr = i; 
						break;
					}
				}
			}
			
			// else move to next instruction
			break;
			
		case '}':
		
			// fall back to corresponding '}'
			for(int i=stringPtr; i>=0; --i)
			{
				if(input.at(i)=='}')
				{
					++counter;
					
				}
				if(input.at(i)=='{')
				{
					--counter;
					
				}
				if(counter == 0)
				{ 
					// pointer NEEDS to point postion BEFORE 
					// corresponding open brace
					stringPtr = i-1; 
					break;
				}
			}
		
			break;
		default:
			cout << "INVALID INPUT: " << command << endl;
	}
}


// loops through a string and passes each character
void cppParser(string code)
{	
	cout << "#include <iostream>\nusing std::cout; using std::endl;\n"
		"\nint tape[1000] = {0};\nint* dp = tape;\n\nint main(){" 
		"\ncout << endl;" << endl;
	
	for(int i=0; i<code.length(); ++i)
	{
		toCPP(code.at(i));
	}
	
	cout << "\n\tcout << endl;\n\treturn 0;\n}" << endl;
}


// converts string of coded input and writes a C++ program
void toCPP(char command)
{
	for(int i=0; i<tabCounter; ++i)
	{
		cout << "\t";
	}
	
	switch(command)
	{	
		case '+':
			cout << "++(*dp);" << endl;
			break;
		case '-':
			cout << "--(*dp);" << endl;
			break;
		case '>':
			cout << "++dp;" << endl;
			break;
		case '<':
			cout << "--dp;" << endl;
			break;
		case ':':
			cout << "cout << *dp;" << endl;
			break;
		case '.':
			cout << "cout << static_cast<char>(*dp);" << endl;
			break;
		case '{':
			cout << "while(*dp){" << endl;
			++tabCounter;
			break;
			
		case '}':
			cout << "}" << endl;
			--tabCounter;
			break;
		default:
			cout << "INVALID INPUT: " << command << endl;
	}
	
}





