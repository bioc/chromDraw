/*
* Name: charsLenghts.h
* Description: Definition chars lengh. Each char lengh in the Px.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#ifndef CHARSLENGHTS_H_
#define CHARSLENGHTS_H_


#include <string>

using namespace std;

class charsLenghts 
{ 
	public:

		/**
		* Get lenght for actual char.
		* @param c Input char.
		* @return Lenght of input char.
		*/
		static double helveticaCharLengh(char c)
		{
			switch (c)
			{
				case 'a':
					return 5.56;
				case 'b':
					return 5.56;
				case 'c':
					return 5.00;
				case 'd':
					return 5.56;
				case 'e':
					return 5.56;
				case 'f':
					return 2.78;
				case 'g':
					return 5.56;
				case 'h':
					return 5.55;
				case 'i':
					return 2.21;
				case 'j':
					return 2.22;
				case 'k':
					return 4.99;
				case 'l':
					return 2.21;
				case 'm':
					return 8.33;
				case 'n':
					return 5.55;
				case 'o':
					return 5.56;
				case 'p':
					return 5.56;
				case 'q':
					return 5.56;
				case 'r':
					return 3.33;
				case 's':
					return 4.99;
				case 't':
					return 2.77;
				case 'u':
					return 5.55;
				case 'v':
					return 5;
				case 'w':
					return 7.23;
				case 'x':
					return 5.00;
				case 'y':
					return 5.00;
				case 'z':
					return 5.00;

				case 'A':
					return 6.68;
				case 'B':
					return 6.67;
				case 'C':
					return 7.22;
				case 'D':
					return 7.21;
				case 'E':
					return 6.67;
				case 'F':
					return 6.10;
				case 'G':
					return 7.76;
				case 'H':
					return 7.21;
				case 'I':
					return 2.76;
				case 'J':
					return 4.99;
				case 'K':
					return 6.67;
				case 'L':
					return 5.56;
				case 'M':
					return 8.32;
				case 'N':
					return 7.21;
				case 'O':
					return 7.76;
				case 'P':
					return 6.67;
				case 'Q':
					return 7.77;
				case 'R':
					return 7.22;
				case 'S':
					return 6.67;
				case 'T':
					return 6.11;
				case 'U':
					return 7.21;
				case 'V':
					return 6.68;
				case 'W':
					return 9.43;
				case 'X':
					return 6.68;
				case 'Y':
					return 6.68;
				case 'Z':
					return 6.11;
		
				case '1':
					return 5.54;
				case '2':
					return 5.56; 
				case '3':
					return 5.56;
				case '4':
					return 5.56;
				case '5':
					return 5.56;
				case '6':
					return 5.56;
				case '7':
					return 5.56;
				case '8':
					return 5.56;
				case '9':
					return 5.56;
				case '0':
					return 5.56;

				case '!':
					return 2.76;
				case '"':
					return 3.55;
				case '#':
					return 5.56;
				case '$':
					return 5.56;
				case '%':
					return 8.87;
				case '\'':
					return 1.9;
				case '(':
					return 3.33;
				case ')':
					return 3.33;
				case '*':
					return 3.88;
				case '+':
					return 5.83;
				case ',':
					return 2.76;
				case '-':
					return 3.33;
				case '.':
					return 2.76;
				case '/':
					return 2.77;
				case ':':
					return 2.75;
				case ';':
					return 2.75;
				case '=':
					return 5.83;
				case '>':
					return 5.83;  
				case '?':
					return 5.57;
				case '@':
					return 10.15;
				case '[':
					return 2.77;
				case '\\':
					return 2.77;
				case ']':
					return 2.77;
				case '^':
					return 4.68;
				case '_':
					return 5.57;
				case '`':
					return 3.32;
				case '{':
					return 3.33;
				case '|':
					return 2.58;
				case '}':
					return 3.33;
				case '~':
					return 5.83;


				default:
					return 5.16;
			}

		}

	/**
	* Get leght of string in pixels.
	* @param s input string.
	* @return Lenght of input string.
	*/
	static float getStringPxLengh(string s)
		{
			float len = 0.0;
			for(unsigned int i=0; i<s.length(); i++)
			{
				len += (float)(helveticaCharLengh(s[i]));
			}

			return len;
		}

};

#endif // CHARSLENGHTS_H_
