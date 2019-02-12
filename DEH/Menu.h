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
		
		Invulnerability,
		SpeedHack,
		Test,
		ChangeLGR,

		AppleCounter,
		DeathCounter,
		ShowGravity,
		ApplesTaken
	};

	enum class MenuItemsID {
		Main,
			GeneralOptions,
				Invulnerability,
				SpeedHack,
				testMenu,
				ChangeLGR,

			DisplayOptions,
				AppleCounter,
				DeathCounter,
				ShowGravity,
				ApplesTaken
		
	};

	enum menuValueType {
		n, //None
		b, //Bool
		i, //Integer
		a, //array
		s  //String
	};

	struct menuValue {
	public:
		MenuValueID ID;
		menuValueType Type;
		std::string Name;
		int Value;
		std::vector<std::string> ArrayValue;
	};

	struct menuItem {
	public:
		MenuItemsID ID;
		std::string Name;
		menuValue* value;
		std::vector<menuItem*>* subMenu;
		menuItem* parent;
	};

	menuItem* createMenuItem(menuItem* parent, MenuItemsID id, std::string Name, MenuValueID ID = MenuValueID::None, menuValueType Type = menuValueType::n, int Value = -1, std::vector<std::string> arrayVal = {});

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
