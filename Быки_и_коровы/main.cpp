#include <iostream>
#include <locale>
#include <ctime>
#include <string>
#include <algorithm>
#include <sstream>
#include <limits>// для чека ввода
#include <fstream>

using namespace std;

// преобразуем int в string
string int_to_string(int hn)
{
	stringstream ss;
	ss << hn;
	string str;
	ss >> str;
	return str;
}

// проверяем повторяются ли цифры в числе
bool check_repeat(int num)
{
	bool check;
	string str = int_to_string(num);
	sort(str.begin(), str.end());
	if(unique(str.begin(), str.end()) == str.end())
	{
		// нет повторений
		check = false;
	}
	else
	{
		// есть повторения
		check = true;
	}
	return check;
}

// генерируем 4-значное случайное число
int init_num()
{
	int hn;
	srand(time(NULL));
	hn = 1000 + rand() % 9999;
	// чекаем инициализацию
	//cout << hn << endl;
	if(check_repeat(hn))
	{
		hn = 0;
		hn = 1000 + rand() % 9999;
		//cout << "Был повтор " << hn << endl;
	}
	return hn;
}

// ввод и проверка числа пользователя
int check_in_num()
{
	int n;
	ostringstream os;
	bool good = true;
	do
	{
		cout << "Введите число: ";
		cin >> n;
		os << n;
		if((!(good = cin.good())) || (os.str().size() < 4))
		{
			cout << "Вы ввели некорректное число!" << endl;
			// очичтить экран и перезасчитать попытку
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}while(!good);
	return n;
}

// считаем быков
void bull(string a, string b)
{
	int k = 0;// счетчик быков
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
	cout << k << " быков." << endl;
	cout << "Быки: " << res << endl;
	// определение выигрыша
	if(k == 4)
	{
		cout << "Вы выиграли!" << endl;
		system("pause");
		exit(0);
	}
}

// считаем коров
void cow(string a, string b)
{
	int k = 0;// счетчик коров
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
	cout << k << " коров." << endl;
	cout << "Коровы: " << res << endl;
}
// проверяем, открыт ли файл, содержащий правила игры
ifstream open_file(string name)
{
	ifstream f(name);
	if(!f.is_open())
	{
		cout << "Файл не открыт! " << name << endl;
	}
	return f;
}

// вывод справки 
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

// основная функция, где играем
void play()
{
	int hidden_num;// загаданное число
	int user_num;// число, вводимое пользователем
	hidden_num = init_num();
	int n = 0;// счетчик попыток
	do
	{
		// ввод пользователем числа
		user_num = check_in_num();
		// переводим в строки, чтобы сравнивать
		string t_string = int_to_string(user_num);
		string h_string = int_to_string(hidden_num);
		bull(h_string, t_string);
		cow(h_string, t_string);
		n++;
	}while(n != 10);
}
// меню игры
int menu()
{
	int c;// для switch-a
	cout << "|1| - справка" << endl;
	cout << "|2| - новая игра" << endl;
	cout << "|3| - выход из игры" << endl;
	cin >> c;
	return c;
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int c;
	cout << "Вас приветствует самый примитивный убийца времени)" << endl;
	c = menu();
	switch (c)
	{
	case 1:
		print_reference();
		// возврат в меню
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