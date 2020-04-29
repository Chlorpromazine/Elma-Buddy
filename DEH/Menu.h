#pragma once

#include "DEH.h"


class Menu {
private:
	
	bool showAppleCounter = true;

public:
	static Menu menu;

	int selOpt = 0;
	int subMenuLev = 1;

	void initMenu();
	
	void incSelOpt();
	void decSelOpt();

	void changeValue(int val);
	void saveSettings();

	void enterSubMenu();
	void exitSubMenu();

	

	enum class MenuValueID {
		None, //For parent menu
		
		AppleCounter,
		DeathCounter,
		ShowGravity,
		TimeAppleTaken,
		LineToObject,
		ShadowKuski,
		ChatTimestamp,

		ChangeLGR,
		DeathDelay,

		Invulnerability,
		SpeedHack
	};

	enum class MenuItemsID {
		Main,
				
			DisplayOptions,
				AppleCounter,
				DeathCounter,
				ShowGravity,
				TimeAppleTaken,
				LineToObject,
				ShadowKuski,
				ChatTimestamp,

			GeneralOptions,
				ChangeLGR,
				DeathDelay,

			WhatIfs,
				Invulnerability,
				SpeedHack
	};

	enum menuValueType {
		n, //None
		b, //Bool
		i, //Integer
		a, //array
		s  //String
	};

	struct range {
	public:
		int min;
		int max;
		range(int MIN, int MAX) {
			if (MIN <= MAX) {
				min = MIN;
				max = MAX;
			}
			else
			{
				min = MAX;
				max = MIN;
			}
		}
		range() {}
	};

	struct menuValue {
	public:
		MenuValueID ID;
		menuValueType Type;
		std::string Name;
		int Value;
		std::vector<std::string> ArrayValue;
		range Range;
	};

	struct menuItem {
	public:
		MenuItemsID ID;
		std::string Name;
		menuValue* value;
		std::vector<menuItem*>* subMenu;
		menuItem* parent;
	};

	
	menuItem* createMenuItem(menuItem* parent, MenuItemsID id, std::string Name, MenuValueID ID = MenuValueID::None, menuValueType Type = menuValueType::n, int Value = -1, std::vector<std::string> arrayVal = {}, range r = range(0,0));

	menuItem* currentMenu;
	
	struct options {
	public:
		std::string Name;
		int value;

		options(std::string n, int v)
		{
			Name = n;
			value = v;
		}
	};

	
	std::map<MenuValueID, int> optionList;

	void getOptions(menuItem* mainMenu);

};
