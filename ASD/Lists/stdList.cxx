#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	int n, val, pos;
	
	cin >> n;

	string input;

	list <int> my_list;

	while (cin)
	{
		getline(cin, input);

		if (input[0] == 'F') // push_front
			my_list.push_front(stoi(input.substr(2)));	
		
	
		if (input[0] == 'B') // push back
			my_list.push_back(stoi(input.substr(2)));
		
	
		if (input[0] == 'b') // pop back
		{	
			if (my_list.size() == 0)
			{
				cout << "EMPTY" << endl;
				continue;
			}

			cout << my_list.back() << endl;
			my_list.pop_back();
		}
		
		if (input[0] == 'f') // pop front
		{	
			if (my_list.size() == 0)
			{
				cout << "EMPTY" << endl;
				continue;
			}
			
			cout << my_list.front() << endl;
			my_list.pop_front();
		}
		
		if (input[0] == 'C') // find
		{
			list<int>::iterator iter = find(my_list.begin(), my_list.end(), stoi(input.substr(2)));
			//pos  = (int)iter;
			if (iter == my_list.end())
				cout << "FALSE" << endl;
			
			
			else
				cout << "TRUE" << endl;
		}

		if (input[0] == 'S')
			cout << my_list.size() << endl;
	}

return 0;
}
