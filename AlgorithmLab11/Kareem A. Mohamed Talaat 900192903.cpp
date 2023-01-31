#include <iostream>
#include <string>
#include <vector>

using namespace std;

int ** get_cost_matrix(vector<string> text, int LW)
{
	int ** cost;
	cost =  new int*[text.size()];
	for (int i = 0; i < text.size(); i++)
	{
		cost[i] = new int[text.size()];
	}
	int temp;
	bool isinf = false;
	int k;
	int infinite = -1;
	
	for (int i = 0; i < text.size(); i++)
	{
		isinf = false;
		k = i;
		temp = 0;
		while ( k < text.size())
		{
			temp = temp + (text[k].size() + (k-i));
			
			if (temp > LW)
			{
				cost[i][k] = infinite;
			}
			else
			{
				cost[i][k] = (LW - temp) * (LW - temp);
			}
			k++;
		}
	}
	return cost;
}

int* get_pointer_array(int ** cost, int n)
{
	
	int* pointer;
	pointer = new int[n];
	int* min_cost = new int[n];
	int temp;
	int i; int j = n - 1; int k;
	int min;
	
		for (i = n - 1; i >= 0; i--)
		{
			j = n - 1;
			temp = 0;
			min = 999999;
			if (cost[i][j] == -1)
			{
				
				while (cost[i][j] == -1)
				{
					j--;
				}
				while (j>=i)
				{
					temp = cost[i][j] + min_cost[j + 1];
					if (temp < min)
					{
						k = j+1;
						min = temp;
					}
					
					j--;
				}
				    pointer[i] = k;
					min_cost[i] = min;
			}
			else
			{
				min_cost[i] = cost[i][j];
				pointer[i] = j + 1;
			}
			
		}
		cout << "\nminimum cost is: " << min_cost[0] << endl;
		return pointer;
}

void display(int* pointer, vector<string> text)
{
	int temp;
	int i = 0;
	int k = 1;
	bool finished = false;
		temp = pointer[i];
		while (!finished)
		{
			
			cout << "line #" << k << " : ";
			for (int j = i; j < temp; j++)
			{
				  cout << text[j] << " ";
				  
				if (text[j] == text.at(text.size()-1))
				{
					
					finished = true;
	
				}
			}
			cout << endl;
			k++;
			i = temp;
			temp = pointer[i];

			
		}
}

void wrap_text(string text, int LW)
{
	string temp;
	vector<string> words;
	int i = 0;
	string delimiter = " ";
	int pos = 0;
	string token;
	while ((pos = text.find(delimiter)) != std::string::npos) {
		token = text.substr(0, pos);
		words.push_back(token);
		text.erase(0, pos + delimiter.length());
	}
	words.push_back(text);
	
	int** cost;
	cost = get_cost_matrix(words, LW);
	int* pointer;
	pointer = get_pointer_array(cost, words.size());
	
	display(pointer, words);
}

int main()
{
	cout << "First Example:" << endl;
	string text;
	text = "Jackie Tom loves to cook";
	cout << "Text is: " << text << endl;
	int L = 10;
	wrap_text(text, L);

	cout << "\n_________________________________________" << endl << endl;

	cout << "Second Example:" << endl;
	string text2;
	text2 = "blah blah blah blah reallylongword";
	cout << "Text is: " << text2 << endl;
	int L2 = 16;
	wrap_text(text2, L2);

	cout << endl;
	system("pause");
	return 0;
}