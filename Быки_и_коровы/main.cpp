#include <iostream>
#include <locale>
#include <ctime>
#include <string>
#include <algorithm>
#include <sstream>
#include <limits>// ��� ���� �����
#include <fstream>

using namespace std;

// ����������� int � string
string int_to_string(int hn)
{
	stringstream ss;
	ss << hn;
	string str;
	ss >> str;
	return str;
}

// ��������� ����������� �� ����� � �����
bool check_repeat(int num)
{
	bool check;
	string str = int_to_string(num);
	sort(str.begin(), str.end());
	if(unique(str.begin(), str.end()) == str.end())
	{
		// ��� ����������
		check = false;
	}
	else
	{
		// ���� ����������
		check = true;
	}
	return check;
}

// ���������� 4-������� ��������� �����
int init_num()
{
	int hn;
	srand(time(NULL));
	hn = 1000 + rand() % 9999;
	// ������ �������������
	//cout << hn << endl;
	if(check_repeat(hn))
	{
		hn = 0;
		hn = 1000 + rand() % 9999;
		//cout << "��� ������ " << hn << endl;
	}
	return hn;
}

// ���� � �������� ����� ������������
int check_in_num()
{
	int n;
	ostringstream os;
	bool good = true;
	do
	{
		cout << "������� �����: ";
		cin >> n;
		os << n;
		if((!(good = cin.good())) || (os.str().size() < 4))
		{
			cout << "�� ����� ������������ �����!" << endl;
			// �������� ����� � ������������� �������
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}while(!good);
	return n;
}

// ������� �����
void bull(string a, string b)
{
	int k = 0;// ������� �����
	string res;
	for(int i = 0; i < a.length(); i++)
	{
		for(int j = 0; j < b.length(); j++)
		{
			if((a[i] == b[j]) && (i == j))
			{
				k++;
				res += a[i];
			}
				
		}
	}
	cout << k << " �����." << endl;
	cout << "����: " << res << endl;
	// ����������� ��������
	if(k == 4)
	{
		cout << "�� ��������!" << endl;
		system("pause");
		exit(0);
	}
}

// ������� �����
void cow(string a, string b)
{
	int k = 0;// ������� �����
	string res;
	for(int i = 0; i < a.length(); i++)
	{
		for(int j = 0; j < b.length(); j++)
		{
			if((a[i] == b[j]) && (i != j))
			{
				k++;
				res += b[j];
			}
				
		}
	}
	cout << k << " �����." << endl;
	cout << "������: " << res << endl;
}
// ���������, ������ �� ����, ���������� ������� ����
ifstream open_file(string name)
{
	ifstream f(name);
	if(!f.is_open())
	{
		cout << "���� �� ������! " << name << endl;
	}
	return f;
}

// ����� ������� 
void print_reference()
{
	ifstream fs;
	string line;
	fs = open_file("rules.txt");
	while(!fs.eof() && fs.is_open())
	{
		getline(fs, line);
		cout << line << endl;
	}
	fs.close();
}

// �������� �������, ��� ������
void play()
{
	int hidden_num;// ���������� �����
	int user_num;// �����, �������� �������������
	hidden_num = init_num();
	int n = 0;// ������� �������
	do
	{
		// ���� ������������� �����
		user_num = check_in_num();
		// ��������� � ������, ����� ����������
		string t_string = int_to_string(user_num);
		string h_string = int_to_string(hidden_num);
		bull(h_string, t_string);
		cow(h_string, t_string);
		n++;
	}while(n != 10);
}
// ���� ����
int menu()
{
	int c;// ��� switch-a
	cout << "|1| - �������" << endl;
	cout << "|2| - ����� ����" << endl;
	cout << "|3| - ����� �� ����" << endl;
	cin >> c;
	return c;
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int c;
	cout << "��� ������������ ����� ����������� ������ �������)" << endl;
	c = menu();
	switch (c)
	{
	case 1:
		print_reference();
		// ������� � ����
		c = menu();
		switch (c)
		{
		case 2:
			system("cls");
			play();
			break;
		case 3:
			exit(0);
			break;
		}
		break;
	case 2:
		play();
		break;
	case 3:
		exit(0);
		break;
	}
	

	system("pause");
	return 0;
}