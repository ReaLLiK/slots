#pragma once
#include <iostream>
#include <map>
#include<math.h>
#include <algorithm>
class Slot_machine
{
	bool choise = 0;
	int field[3][5];
	int win_lines[8][5] =
	{
		{0,0,0,0,0},
		{1,1,1,1,1},
		{2,2,2,2,2},
	    {0,1,2,1,0},
		{2,1,0,1,2},
		{0,1,1,1,2},
		{1,2,2,2,1},
		{2,1,1,1,0}
	};
	int wins_table[6][3] =
	{
		{10,20,30},
		{15,30,45},
		{15,30,45},
		{20,40,60},
		{20,40,60},
		{20,40,60}
	};
	int lines[5][8];
	int total_win = 0;
	int symbol=5;
	int lenth = 0;
	std::map<int, int> expectation = {{10,0},{15,0}, {20,0}, {30,0}, {40,0}, {45,0}, {60,0}};
	double exp = 0;
	double disp;
	void ask_type()
	{
		std::cout << "0-Random    1-Input\n";
		std::cin >> choise;
	}
	void generate_field()
	{
		if (choise == 0)
		{
			for (int i = 0; i < 3; ++i)
			{
				for (int j=0; j<5; ++j)
					field[i][j] = rand() % 6;
			}
			return;
		}
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 5; ++j)
				std::cin>>field[i][j];
		}
	}
	void parse_lines()
	{
		for (int j = 0; j < 8; ++j)
		{
			for (int i = 0; i < 5; ++i)
			{
				lines[i][j] = field[win_lines[j][i]][i];
			}
		}
	}
	void count_win()
	{
		for (int j = 0; j < 8; ++j)
		{
			for (int i = 0; i < 5; ++i)
			{
				if (symbol == 5)
				{
					symbol = lines[i][j];
				}
				if (lines[i][j]==symbol||lines[i][j]==5)
				{
					lenth++;
					continue;
				}
				break;
			}
			if (lenth > 2)
			{
				total_win += wins_table[symbol][lenth - 3];
				expectation[wins_table[symbol][lenth - 3]]++;
			}
			lenth = 0;
			symbol = 5;
		}
	}
public:
	void play()
	{
		//ask_type();
		generate_field();
		std::cout << "field:\n";
		for (int i=0; i<3; ++i)
		{
			for (int j=0; j<5;++j)
			{
				std::cout << field[i][j] << ' ';
			}
			std::cout << '\n';
		}
		parse_lines();
		std::cout << "lines:\n";
		for (int j = 0; j < 8; ++j)
		{
			for (int i = 0; i < 5; ++i)
				std::cout << lines[i][j] << ' ';
			std::cout<<'\n';
		}
		count_win();
		std::cout << "Win=" << total_win<<'\n';
		for (auto i : expectation)
		{
			std::cout << i.first << "	" << i.second <<'\n';
		}
	}
	void testing()
	{
		for (int i = 0; i < 1000000; ++i)
		{
			play();
			total_win = 0;
		}
		for (auto j : expectation)
		{
			std::cout<<'\n' << j.first << "	" << j.second << '\n';
		}
		for (auto k : expectation)
		{
			exp += (double)k.first * (double)k.second / 1000000;
		}
		disp = pow(exp, 2);
		for (auto k : expectation)
		{
			disp -= (double)k.first*(double)k.first * (double)k.second / 1000000;
		}
		//МО для 1кк 31.4125 диспа примерно 30 для 100к
		//Для 3 некорелирующих линий МО 11.8029 1кк итераций
		//диспа 220 для 3 независимых лайнов для 1 кк
		//Таким образом получили очень маленькую кореляцию между лайнами и можно считать МО как независимые переменные
		std::cout << "\n" << exp << '\n';
		std::cout << "\n" << disp << '\n';
	};
};