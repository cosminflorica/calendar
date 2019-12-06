#include "Engine.h"
#include<iostream>
#include<iomanip>
#include <string>
#include<stdlib.h>
#include<conio.h>


namespace engine {
	
	/*vectori cu lunile anului si zilele saptamanii*/
	const char*	name_month[12] = {
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December" };
	const char* name_day[7]{
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday"
		 };

	/*vector lungime luni -- Februarie 29 - Leap year*/
	int	month_length[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	/*doomsdates array - Ianuarie 4, Februarie 29 on Leap year*/
	int	doomsdates[12] = { 3, 28, 14, 4, 9, 6, 11, 8, 5, 10, 7, 12 };

	/*data introdusa de la tastatura*/
	int			input_year;
	int			input_month;
	int			input_day;

	short int	doomsday;
	bool		is_leap_year = false;


	

	void start_calendar() {

		print_menu(1);

		int touchedKey = _getch()-'0';
		std::cout << touchedKey;

		if (touchedKey == 1) {
			print_menu(2);

		}

	}
	
	void		read_year()
	{
		char date[11];
		do {
				//system("@cls||clear"); /*clears the console for next do*/
				std::cout << "\nPlease insert a valid date (dd.mm.yyyy): ";
				std::cin >> date;
				
				if (date[0] == '0') {
					start_calendar();
					break;
				}
				else {
					int count = 0;
					char* ptr;
					ptr = strtok(date, ".");
					while (ptr != NULL) {
						if (count == 0) input_day = atoi(ptr);
						if (count == 1) input_month = atoi(ptr);
						if (count == 2) input_year = atoi(ptr);
						count++;
						ptr = strtok(NULL, ".");
					}
					
				}

			} while( input_year <= 1499 || input_year > 5001 || input_day < 0 || input_day > 31 || input_month < 0 || input_month > 12);
	}

	/**/
	int			get_century_code() {
		if (input_year % 400 / 100 == 3) return 3;
		if (input_year % 400 / 100 == 0) return 2;
		if (input_year % 400 / 100 == 1) return 0;
		if (input_year % 400 / 100 == 2) return 5;
	}

	/*For every year there are certain dates that are in the same day of the week - there are called 'doomsdays'.
	These dates are: 3 January (or 4 for leap year), 28 February ( 29 for leap year ), 14 March, 4 April, 9 May, 6 June, 11 July, 8 August, 5 September,10 October, 7 November, 12 December
	All these dates are in the same day of the week. For instance, in 2019 all these dates are Thursdays.
	Based on that, you can apply an algorithm developed by John H Conway to the doomsday for every year.*/
	int			get_doomsday()
	{
		/*if is a leap year the February has 29 days and the doomsdates for January and February changes*/
		if (is_leap_year) {
			month_length[1] = 29;
			doomsdates[0] = 4;
			doomsdates[1] = 29;
		}


		/*dates needed for algrithm*/
		int _centurycode = get_century_code();
		int _div12 = input_year % 100 / 12;
		int _mod12 = (input_year % 100 ) %12;
		int _div4 = (input_year % 100) % 12 / 4;

		return (get_century_code()+_div12+_mod12+_div4) % 7;
	}

	/*A leap year is every 4 years, but not every 100 years, then again every 400 years.*/
	void		set_leap_year() {
		if ((input_year / 4) * 4 == input_year)
		{
			if (input_year / 400 * 400 == input_year)
			{
				is_leap_year = 1;
			}
			else if (input_year / 100 * 100 == input_year)
			{
				is_leap_year = 0;
			}
			else is_leap_year = 1;
		}
		else is_leap_year = 0;
	}
	
	/*Based on the doomsday for the input year, this function gets the exact day of the week for every specific date
	It does that by */
	void		get_day_of_the_week()
	{

		int		_doomsday = get_doomsday();
		int		day_of_the_week;

		/*if the input date is bigger than the doomsday for that specific month, it adds the date to the doomsday and 
		apply modulo 7 to get the index of the day 0-Sunday, 1-Monday, etc
		if the date is smaller that the doomsday, it substracts the date and so on..*/
		if (doomsdates[input_month - 1] - input_day > 0)
		{
			day_of_the_week = _doomsday - ((doomsdates[input_month - 1] - input_day)) % 7;
			if (day_of_the_week < 0) day_of_the_week+=7;
		}
		else { 
			day_of_the_week = (_doomsday + ((-1) * (doomsdates[input_month - 1] - input_day)) % 7 ) % 7; 
		}
		std::cout << "\nDay of the week for "<<input_day<<"."<<input_month<<"."<<input_year<<": " << name_day[day_of_the_week] <<"\n\n";
	}

	void		print_menu(int MenuChoice) {
		switch (MenuChoice) {
		case 1:
			system("cls");
			std::cout << "\n\tCalendar Application using John H. Conway algorithm";
			std::cout << "\n--------------------------------------------------------------------\n";
			std::cout << "\n--------------------------------------------------------------------\n";
			std::cout << "\n1. Weekday Calculator - What day is this date?";
			std::cout << "\n2. ";
			std::cout << "\n4. Exit application.";
			std::cout << "\n\n--------------------------------------------------------------------\n";
			std::cout << "\nChoose your option.. ";
			break;
		case 2:
			system("cls");
			std::cout << "\n\tCalendar Application using John H. Conway algorithm";
			std::cout << "\n--------------------------------------------------------------------\n";
			std::cout << "\n--------------------------------------------------------------------\n";
			std::cout << "\n\t   Weekday Calculator - What day is this date?"; 
			std::cout << "\n\t        ** Press 0 to go back to menu **";
			std::cout << "\n--------------------------------------------------------------------\n";
			read_year();
			set_leap_year();
			get_day_of_the_week();
			std::cout << "\n\n--------------------------------------------------------------------\n";
			break;
		case 3:
			system("cls");
			std::cout << "\n\tCalendar Application using John H. Conway algorithm";
			std::cout << "\n--------------------------------------------------------------------\n";
			std::cout << "\n--------------------------------------------------------------------\n";
			std::cout << "\n1. Weekday Calculator - What day is this date?";
			std::cout << "\n2. ";
			std::cout << "\n4. Exit application.";
			std::cout << "\n\n--------------------------------------------------------------------\n";
			std::cout << "\nChoose your option.. ";
			break;
		}
	}
}