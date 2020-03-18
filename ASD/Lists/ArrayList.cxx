#include <iostream>
#include <string>
#include "ArrayList.hxx"

using namespace std;

int main()
{
	int n, val, pos;
	
	cin >> n;

	string input;

	ArrayList list (n);

	while (cin)
	{
		getline(cin, input);

		if (input[0] == 'F') // push_front
			list.push_front(stoi(input.substr(2)));	
		
	
		if (input[0] == 'B') // push back
			list.push_back(stoi(input.substr(2)));
		
	
		if (input[0] == 'b') // pop back
		{	
			if (list.size() == 0)
			{
				cout << "EMPTY" << endl;
				continue;
			}

			cout << list.pop_back() << endl;
		}
		
		if (input[0] == 'f') // pop front
		{	
			if (list.size() == 0)
			{
				cout << "EMPTY" << endl;
				continue;
			}
			
			cout << list.pop_front() << endl;
		}
		
		if (input[0] == 'C') // find
		{
			pos = list.find(stoi(input.substr(2)));
			
			if (pos == -1)
				cout << "FALSE" << endl;
			
			
			else
				cout << "TRUE" << endl;
		}

		if (input[0] == 'S')
			cout << list.size() << endl;
	}

return 0;
}
