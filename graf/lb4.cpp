/*23. В  файле  записаны  предложения по обмену жилплощадью в
пределах некоторого города, включающие пожелания по количеству
комнат, наличию балкона и телефона.Имеются варианты размена
одной квартиры на 2 других либо наоборот.Требуется по заявке
клиента  предложить способы обмена.Предусмотреть возможность
нахождения циклических обменов, в которых участвуют более двух
сторон.Найденные варианты выдать в порядке возрастания числа
участвующих в обмене сторон.Считать, что клиентам  подходят
более хорошие по сравнению с их требованиями варианты переезда
(11).*/
#include <iostream>
#include <conio.h>
#include "windows.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <string>
#include <clocale>
#include <fstream>
using namespace std;

string fileName;
struct propertys //имущество
{
	int numberOfRooms;
	bool isTelefone;
	bool isBolkon;
};


struct clients
{
	string Name;
	vector<propertys> Property; // имущество его
	vector<propertys> Application; //желает
};
bool charInBool(char ch) {
	if (ch == '+') {
		return true;
	}
	return false;
}

void ClientsToFile(vector<clients>& Clients)
{
	ifstream file(fileName);
	clients client;
	propertys property;
	vector<propertys> Propertys;
	vector<propertys> Applications;
	propertys application;
	string line;
	string name;
	int i = 0;
	while (getline(file, line)) 
	{
		while (line[i] != ' ') 
		{
			name += line[i];
			i++;
		}
		client.Name = name;
		i++;
		name.clear();
		while (line[i] != ';')
		{
			property.numberOfRooms = int(line[i]) - '0';
			i++;
			property.isBolkon = charInBool(line[i]);
			i++;
			property.isTelefone = charInBool(line[i]);
			i++;
			if (line[i] == ',')
			{
				Propertys.push_back(property);
				i++;
			}
		}
		i++;
		Propertys.push_back(property);
		client.Property = Propertys;
		Propertys.clear();
		while (line[i] != '.')
		{
			application.numberOfRooms = int(line[i]) - '0';
			i++;
			application.isBolkon = charInBool(line[i]);
			i++;
			application.isTelefone = charInBool(line[i]);
			i++;
			if (line[i] == ',') 
			{
				Applications.push_back(application);
				i++;
			}
		}
		Applications.push_back(application);
		client.Application = Applications;
		Applications.clear();
		Clients.push_back(client);
		line.clear();
		i = 0;
	}
	file.close();
}

void inichalizMatrixAdjacency(vector<clients>& Clients, vector<vector<int>>& matrix)
{
	for (int i = 0; i < Clients.size(); i++)
	{
		vector<int> row;
		for (int j = 0; j < Clients.size(); j++)
		{
			row.push_back(0);
		}
		matrix.push_back(row);
	}
}

bool isAssepteble(clients clientOneApplications, clients clientTwoProperty) // хочет == надо
{
	int sizeApplication = clientOneApplications.Application.size();
	int sizePropertyOne = clientOneApplications.Property.size();

	int sizeApplicationTwo = clientTwoProperty.Application.size();
	int sizeProperty = clientTwoProperty.Property.size();
	bool flag = false;
	int flagInt = -1;

	//if (((sizePropertyOne == 2) && (sizeApplicationTwo == 1)) || ((sizePropertyOne == 1) && (sizeApplicationTwo == 2)))
	//{
		if (sizeApplication == 1)
		{
			for (int j = 1; j <= sizeProperty; j++)
			{
				if (clientOneApplications.Application[0].numberOfRooms <= clientTwoProperty.Property[j - 1].numberOfRooms)
				{
					if (clientOneApplications.Application[0].isBolkon <= clientTwoProperty.Property[j - 1].isBolkon)
					{
						if (clientOneApplications.Application[0].isTelefone <= clientTwoProperty.Property[j - 1].isTelefone)
						{
							flag = true;
						}
						else
						{
							flag = false;
						}
					}
					else
					{
						flag = false;
					}
				}
				
				else
					flag = false;
			}
			if (flag == true) 
			{

				return true;
			}
			else
			{
				return false;
			}
		}
		else if (sizeApplication == 2) 
		{
			set<int> indexPropertyOne{};
			set<int> indexPropertyTwo{};
			for (int j = 1; j <= sizeProperty; j++)
			{
				if (clientOneApplications.Application[0].numberOfRooms < clientTwoProperty.Property[j - 1].numberOfRooms)
				{
					indexPropertyOne.insert(j);
				}
				else if (clientOneApplications.Application[0].numberOfRooms == clientTwoProperty.Property[j - 1].numberOfRooms)
				{
					if (clientOneApplications.Application[0].isBolkon <= clientTwoProperty.Property[j - 1].isBolkon)
					{
						if (clientOneApplications.Application[0].isTelefone <= clientTwoProperty.Property[j - 1].isTelefone)
						{
							indexPropertyOne.insert(j);
						}
					}
				}			
			}
			if (indexPropertyOne.empty())
			{
				return false;
			}
			else
			{
				for (int j = 1; j <= sizeProperty; j++)
				{
					if (clientOneApplications.Application[1].numberOfRooms < clientTwoProperty.Property[j - 1].numberOfRooms)
					{
						indexPropertyTwo.insert(j);
					}
					else if (clientOneApplications.Application[1].numberOfRooms == clientTwoProperty.Property[j - 1].numberOfRooms)
					{
						if (clientOneApplications.Application[1].isBolkon <= clientTwoProperty.Property[j - 1].isBolkon)
						{
							if (clientOneApplications.Application[1].isTelefone <= clientTwoProperty.Property[j - 1].isTelefone)
							{
								indexPropertyTwo.insert(j);
							}
						}
					}
				}
				if (indexPropertyTwo.empty())
				{
					return false;
				}
				else
				{
					//рассматриваем два множества
					if ((indexPropertyOne.size() == 1) && (indexPropertyTwo.size() == 1) && (indexPropertyOne == indexPropertyTwo))
					{
						return false;
					}
					else
					{
						return true;
					}
				}
			}
		
		//}
	}
	else
	{
		return false;
	}
}

void matrixAdjacency(vector<clients>& Clients, vector<vector<int>> & matrix)
{
	vector<propertys> flagProperty;
	for (int i = 0; i < Clients.size(); i++) 
	{
		for (int j = 0; j < Clients.size(); j++)
		{
			if (i == j)
			{
				matrix[i][j] = 0;
			}
			else if (isAssepteble(Clients[i], Clients[j]))
			{
				matrix[i][j] = 1;
				//flagProperty = Clients[i].Application;
				//Clients[i].Application = Clients[j].Application;
				//Clients[j].Application = flagProperty;

			}
			else
			{
				matrix[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < Clients.size(); i++)
	{
		for (int j = 0; j < Clients.size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

}

void findCyclesRecursive(vector<vector<int>>& matrix, vector<clients>& Clients,
	int vertex, vector<int>& path, vector<bool>& visited, vector<vector<int>>& cycles) 
{
	for (int i = 0; i < Clients.size(); i++)
	{
		if (matrix[vertex][i] == 1) {
			if (!visited[i]) {
				path.push_back(i);
				visited[i] = true;
				findCyclesRecursive(matrix, Clients, i, path, visited, cycles);
				path.pop_back();
				visited[i] = false;
			}
			else if (find(path.begin(), path.end(), i) != path.end()) 
			{
				vector<int> cycle;
				auto it = find(path.begin(), path.end(), i);
				cycle.insert(cycle.end(), it, path.end());
				cycle.push_back(i);
				cycles.push_back(cycle);
			}
		}
	}
}

set<int> getCycleSet(const vector<int>& cycle)
{
	return set<int>(cycle.begin(), cycle.end());
}

void findCycles(vector<vector<int>>& matrix, vector<clients>& Clients) 
{
	int n = Clients.size();
	vector<vector<int>> cycles;
	vector<bool> visited(n, false);
	vector<int> path;

	for (int i = 0; i < n; i++) 
	{
		path.push_back(i);
		visited[i] = true;
		findCyclesRecursive(matrix, Clients, i, path, visited, cycles);
		path.pop_back();
		visited[i] = false;
	}

	set<set<int>> uniqueCycleSets; 
	vector<vector<int>> uniqueCycles;

	for (const auto& cycle : cycles)
	{
		set<int> cycleSet = getCycleSet(cycle); 
		if (uniqueCycleSets.find(cycleSet) == uniqueCycleSets.end()) {
			uniqueCycleSets.insert(cycleSet); 
			uniqueCycles.push_back(cycle);  
		}
	}

	sort(uniqueCycles.begin(), uniqueCycles.end(),
		[](const vector<int>& a, const vector<int>& b)
		{
			return a.size() < b.size();
		});

	for (const auto& cycle : uniqueCycles)
	{
		cout << "Обмен: ";
		for (int vertex : cycle) 
		{
			cout << Clients[vertex].Name << " ";
		}
		cout << endl;
	}
}

int main() {
	vector<clients> Client;
	setlocale(LC_CTYPE, "rus");
	cout << "Введите входной файл" << endl;
	cin >> fileName;
	ClientsToFile(Client);
	vector<vector<int>>  matrix;
	inichalizMatrixAdjacency(Client, matrix);
	matrixAdjacency(Client, matrix);
	findCycles(matrix, Client);
}