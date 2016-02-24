
#include <iostream>
using std::cout; using std::endl;

int tape[1000] = {0};
int* dp = tape;

int main(){
cout << endl;
	++(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	while(*dp){
		++dp;
		++(*dp);
		++(*dp);
		++(*dp);
		++(*dp);
		while(*dp){
			++dp;
			++(*dp);
			++(*dp);
			++dp;
			++(*dp);
			++(*dp);
			++(*dp);
			++dp;
			++(*dp);
			++(*dp);
			++(*dp);
			++dp;
			++(*dp);
			--dp;
			--dp;
			--dp;
			--dp;
			--(*dp);
			}
		++dp;
		++(*dp);
		++dp;
		++(*dp);
		++dp;
		--(*dp);
		++dp;
		++dp;
		++(*dp);
		while(*dp){
			--dp;
			}
		--dp;
		--(*dp);
		}
	++dp;
	++dp;
	cout << static_cast<char>(*dp);
	++dp;
	--(*dp);
	--(*dp);
	--(*dp);
	cout << static_cast<char>(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	cout << static_cast<char>(*dp);
	cout << static_cast<char>(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	cout << static_cast<char>(*dp);
	++dp;
	++dp;
	cout << static_cast<char>(*dp);
	--dp;
	--(*dp);
	cout << static_cast<char>(*dp);
	--dp;
	cout << static_cast<char>(*dp);
	++(*dp);
	++(*dp);
	++(*dp);
	cout << static_cast<char>(*dp);
	--(*dp);
	--(*dp);
	--(*dp);
	--(*dp);
	--(*dp);
	--(*dp);
	cout << static_cast<char>(*dp);
	--(*dp);
	--(*dp);
	--(*dp);
	--(*dp);
	--(*dp);
	--(*dp);
	--(*dp);
	--(*dp);
	cout << static_cast<char>(*dp);
	++dp;
	++dp;
	++(*dp);
	cout << static_cast<char>(*dp);
	++dp;
	++(*dp);
	++(*dp);
	cout << static_cast<char>(*dp);

	cout << endl;
	return 0;
}

