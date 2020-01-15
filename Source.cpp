#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool RowColumnEquality(vector<vector<char>> & matrix)
{
	bool check = false;
	for (unsigned int a = 0 ; a < matrix.size() ; a++)
	{
		for (unsigned int b = 0 ; b < matrix.size() ; b++ )
		{
			if(( matrix[a].size() != matrix[b].size()) && !check)
			{
				cout << "Invalid matrix - inconsistent dimensions " << endl ;
				check= true; 
			}
		}
	}	return check;
}

void matrixCall(unsigned int k, unsigned int j,vector<vector<char>> & matrix)
{
	for (unsigned int j=0; j < matrix.size(); j++)
	{   
		for (unsigned int k=0; k < matrix[0].size(); k++)
		{   
			cout << matrix[j][k] << " " ;
		}   cout << endl;
	}
}

int main()
{
	ifstream read;
	string puzzle;
	cout << "Please enter the name of the puzzle file: ";
	cin >> puzzle;

	read.open(puzzle.c_str());

	while(read.fail())
	{
		cout << " File could not be opened" << endl;
		cout << "Please enter the name of the puzzle file: ";
		cin >> puzzle;
		read.open(puzzle.c_str());
	}
	string item;
	while(getline(read,item))
	{
		for(unsigned int letter = 0 ; letter < item.length() ; letter++ )
		{
			if(item.at(letter) > 96 && item.at(letter) < 123 && letter < item.length()-1)
			{
				if((item.at(letter+1) > 96 && item.at(letter+1) < 123))
				{
					cout << "Invalid matrix - cell entry is not a char" << endl ;
					return 0 ;
				}
			}
		}
	}	read.close();
	read.open(puzzle.c_str());
	
	vector<vector<char>> matrix;
	vector<vector<char>> newMatrix;	
	
		for (unsigned int tireX=0; tireX < matrix.size(); tireX++)
		{   
			for (unsigned int tireY=0; tireY < matrix[0].size(); tireY++)
			{   
				newMatrix[tireX][tireY] = '_' ;
			}   cout << endl;
		}	
	char item2;
	while(getline(read,item))
	{    
		vector <char> creat;
		istringstream order(item);

		while(order >> item2)
		{
			creat.push_back(item2);
		}
		matrix.push_back(creat);
	}
	read.close();
	read.open(puzzle.c_str());

	while(getline(read,item))
	{
		for(unsigned int c = 0 ; c < item.length() ; c++ )
		{
			if((item.at(c) < 96 || item.at(c) > 123) && item.at(c) != 32 && item.at(c) != '\t')
			{
				cout << "Invalid matrix - char not lowercase letter" << endl ;
				cin.get();
				cin.ignore();
				return 0 ;
			}
		}
	}	read.close();
	read.open(puzzle.c_str());

	if (RowColumnEquality(matrix))
	{
		cin.get();
		cin.ignore();
		return 0;
	}
	read.close();
	ifstream read2;
	string dictionary;
	vector<string> dic;

	cout << "Please enter the name of the dictionary file: ";
	cin >> dictionary;
	read2.open(dictionary.c_str());

	while(read2.fail())
	{
		cout << " File could not be opened" << endl;
		cout << "Please enter the name of the dictionary file: ";
		cin >> dictionary;
		read2.open(dictionary.c_str());
	}	cout << endl ;

	string word;
	while(read2>>word)
	{
		dic.push_back(word);
	}	read2.close();

	unsigned int j=0,k=0;
	matrixCall(j,k,matrix);
	cout << endl ;

	unsigned int x, y, score = 0;
	bool check2 = true;
	
	while (check2)
	{ 		
		bool control=true;
		string move, path;

		cout << endl << "Enter the starting location for word (x, y): ";
		cin >> x >> y;

		if(x == -1 || y == -1 )
		{
			cout << "You didn't completely solve the puzzle." << endl ;
			cout << "Your final score is " << score << "." << endl;
			return 0 ;
		}
		if(x >= matrix.size() || 0 > x || y >= matrix[0].size() || 0 > y)
		{
			cout <<"Invalid coordinate - out of range" << endl << endl;
			matrixCall(j,k,matrix);
			cout << endl << "Enter the starting location for word (x, y): ";
			cin >> x >> y;
			if(x == -1 || y == -1 )
			{
				cout << endl << "You didn't completely solve the puzzle." << endl ;
				cout << "Your final score is " << score << "." << endl ;
				return 0 ;
			}
		}
		cout << "Enter the path: ";
		cin >> path;

		string kelime = "" ;
		kelime = kelime + matrix[x][y];

		vector<vector<char>> copy;
		copy = matrix ;
		copy[x][y] = '_' ;
		
		bool check = true;
		for(unsigned int charSelect=0 ; charSelect < path.length() ; charSelect++)
		{
			move = path.substr(charSelect,1);	
			if(path.length() < 2 )
			{
				cout << "Invalid path - path too short" << endl << endl;
				matrixCall(j,k,matrix);
				cout << endl << "Enter the starting location for word (x, y): " << endl << "Enter the path:";
				cin >> x >> y;
				if(x == -1 || y == -1 )
				{
					cout << endl << "You didn't completely solve the puzzle." << endl ;
					cout << "Your final score is " << score << "." ;
					return 0 ;
				}
			}
			if(move != "r" && move != "u" && move != "d" && move != "l")
			{
				cout << "Invalid path - non-RLUD input " << endl;
			}
			if(move == "r")  
			{   			  
				if(y  == matrix[0].size()-1)
				{
					cout << "Invalid path - out of range" << endl << endl ;
					matrixCall(j,k,matrix);
					cout << endl << endl ;
					control= false;					
					y--;
				}
				else
				{
					if(matrix[x][y+1] == '_' && control)
					{
						cout << "Invalid path - cell visited previously" << endl << endl;
						matrixCall(j,k,matrix);
					    cout << endl << endl ;
						control= false;
					}
				/*	else if(copy[x][y+1]== '_' && control)
					{
						cout << "Invalid path - cell visited twice" << endl << endl;
						matrixCall(j,k,matrix);
						cout << endl << endl ;
						control= false;				
					}*/
					if(control)
					{  kelime = kelime + matrix[x][y+1];
					copy[x][y+1] = '_' ;
					y++;	}
				}
			}
			if(move == "u")  
			{   			  
				if(x == 0 && control)
				{
					cout << "Invalid path - out of range" << endl << endl;
					matrixCall(j,k,matrix);
					cout << endl << endl ;
					control= false;					
					x++;
				}	
				else
				{
					if(matrix[x-1][y] == '_' && control)
					{
						cout << "Invalid path - cell visited previously" << endl ;
						matrixCall(j,k,matrix);
						cout << endl << endl;
						control= false;		
					}
					/*else if(copy[x-1][y]== '_' && control)
					{
						cout << "Invalid path - cell visited twice" << endl << endl;
						matrixCall(j,k,matrix);
						cout << endl << endl;
						control= false;					
					}*/
					if(control)
					{ kelime = kelime + matrix[x-1][y];
					copy[x-1][y] = '_' ;
					x--;	}
				}
			}
			if(move == "d" )  
			{   			   
				if(x == matrix.size()-1 && control)
				{
					cout << "Invalid path - out of range" << endl << endl ;
					matrixCall(j,k,matrix);
					cout << endl << endl ;
					control= false;					
					x--;
				}
				else
				{   
					if(matrix[x+1][y] == '_' && control)
					{
						cout << "Invalid path - cell visited previously" << endl << endl;
						matrixCall(j,k,matrix);
						cout << endl << endl ;
						control= false;					
					}
					/*else if(copy[x+1][y]== '_' && control)
					{
						cout << "Invalid path - cell visited twice" << endl << endl;
						matrixCall(j,k,matrix);
						cout << endl << endl ;
						control= false;
					}*/
					kelime = kelime + matrix[x+1][y];
					if(control)
					{ copy[x+1][y] = '_' ;
						x++;	}
				}
			}
			if(move == "l")  
			{   			    
				if(y == 0 && control )
				{
					cout << "Invalid path - out of range" << endl << endl ;
					matrixCall(j,k,matrix);
					cout << endl << endl;
					control= false;
						y++;	}	
				else
				{
					if(matrix[x][y-1] == '_' && control)
					{
						cout << "Invalid path - cell visited previously" << endl << endl;
						matrixCall(j,k,matrix);
						cout << endl << endl;
						control= false;
					}
					/*else if(copy[x][y-1]== '_' && control)
					{
						cout << "Invalid path - cell visited twice" << endl << endl ;
						matrixCall(j,k,matrix);
						cout << endl << endl;
						control= false;
					}*/
					if(control)
					{ 
						kelime = kelime + matrix[x][y-1];
						copy[x][y-1] = '_' ;
						y--;
					}
				}
			}
		} 
		bool check3= true;		
		for(unsigned int sozluk = 0 ; sozluk < dic.size() ; sozluk++)
		{
			if(dic[sozluk] == kelime)
			{				
				score = score + (kelime.length() * kelime.length()) ;
				cout << "Word found:" << kelime << endl ;
				cout << "Word length:" << kelime.length() << endl ;
				cout << "Points gained:" << kelime.length() * kelime.length() << endl ;
				cout << "Current score:" << score << endl ;
				cout << endl ;
				matrix = copy ;
				check3=false;

				for (unsigned int j=0; j < matrix[0].size(); j++)
				{   
					for (unsigned int k=0; k < matrix.size(); k++)
					{   
						cout << matrix[j][k] << " " ;
					}	 cout << endl;
				}
			}
		}
		if(check3 && control)
		{
			cout << "Invalid word - non-existent word " << "\"" << kelime << "\"" << endl;
		}
		if(matrix == newMatrix)
		{
			cout << "Congratulations, you have solved the puzzle perfectly!" << endl << "Your final score is " << score << "." << endl ;
			check2=false;
		}
	} return 0;
}
