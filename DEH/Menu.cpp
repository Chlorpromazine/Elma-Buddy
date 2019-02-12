#pragma once

#include "Menu.h"

Menu Menu::menu;

//Initializes the menu
void Menu::initMenu()
{
	
	menuItem* mainMenuItem;
	menuItem* newsubMenuItem;

	//Create the main menu
	mainMenuItem = createMenuItem(NULL, MenuItemsID::Main, std::string("Main"));

	currentMenu = mainMenuItem;
		
		
	//General options
	newsubMenuItem = createMenuItem(mainMenuItem, MenuItemsID::GeneralOptions, std::string("General Options"));
	//todo: add this line to function above?
	newsubMenuItem->parent->subMenu->push_back(newsubMenuItem);


	//General options submenus
	newsubMenuItem = createMenuItem(newsubMenuItem, MenuItemsID::Invulnerability, std::string("Invulnerability"), MenuValueID::Invulnerability, menuValueType::b, false);
	newsubMenuItem->parent->subMenu->push_back(newsubMenuItem);

	newsubMenuItem = createMenuItem(newsubMenuItem->parent, MenuItemsID::testMenu, std::string("test"), MenuValueID::Test, menuValueType::b, false);
	newsubMenuItem->parent->subMenu->push_back(newsubMenuItem);

	newsubMenuItem = createMenuItem(newsubMenuItem->parent, MenuItemsID::SpeedHack, std::string("Speed Hack"), MenuValueID::SpeedHack, menuValueType::i, 600);
	newsubMenuItem->parent->subMenu->push_back(newsubMenuItem);
		

	newsubMenuItem = createMenuItem(newsubMenuItem->parent, MenuItemsID::ChangeLGR, std::string("Change LGR"), MenuValueID::ChangeLGR, menuValueType::a, Level::lev.LGRselected, Level::lev.LGRlist);
	newsubMenuItem->parent->subMenu->push_back(newsubMenuItem);



	//Display Options
	newsubMenuItem = createMenuItem(mainMenuItem, MenuItemsID::DisplayOptions, std::string("Display Options"));
	newsubMenuItem->parent->subMenu->push_back(newsubMenuItem);
	
	//Apple Counter
	newsubMenuItem = createMenuItem(newsubMenuItem, MenuItemsID::AppleCounter, std::string("Apple Counter"), MenuValueID::AppleCounter, menuValueType::b, false);
	newsubMenuItem->parent->subMenu->push_back(newsubMenuItem);

	//Finish/Death counter
	newsubMenuItem = createMenuItem(newsubMenuItem->parent, MenuItemsID::DeathCounter, std::string("Finish/Death Counter"), MenuValueID::DeathCounter, menuValueType::b, false);
	newsubMenuItem->parent->subMenu->push_back(newsubMenuItem);

	//Show Gravity
	newsubMenuItem = createMenuItem(newsubMenuItem->parent, MenuItemsID::ShowGravity, std::string("Apple Gravity"), MenuValueID::ShowGravity, menuValueType::b, false);
	newsubMenuItem->parent->subMenu->push_back(newsubMenuItem);
		
	//Show apples taken (for apple battle)
	newsubMenuItem = createMenuItem(newsubMenuItem->parent, MenuItemsID::ApplesTaken, std::string("Apples Taken"), MenuValueID::ApplesTaken, menuValueType::b, false);
	newsubMenuItem->parent->subMenu->push_back(newsubMenuItem);




	getOptions(currentMenu);


	

}

Menu::menuItem* Menu::createMenuItem(menuItem* parent, MenuItemsID id, std::string Name, MenuValueID ID, menuValueType Type, int Value, std::vector<std::string> arrayVal)
{
	
	menuItem* newMenuItem = new menuItem;
	menuValue* newmenuValue = new menuValue;

	try {
		newmenuValue->ID = ID;
		newmenuValue->Type = Type;
		newmenuValue->Name = Name + std::string("Val");
		newmenuValue->Value = Value;
		newmenuValue->ArrayValue = arrayVal;

		newMenuItem->ID = id;
		newMenuItem->Name = Name;
		newMenuItem->subMenu = new std::vector<menuItem*>; //Add submenus after creating the parent menu.
		newMenuItem->parent = parent;
		newMenuItem->value = newmenuValue;

	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return newMenuItem;
}

void Menu::getOptions(menuItem* Menu)
{
	menuItem* tmpMenu = Menu;
	menuItem* selMenu;

	
	for (int i = 0; i < tmpMenu->subMenu->size(); i++)
	{
		selMenu = tmpMenu->subMenu->at(i);
		
		optionList[selMenu->value->ID] = selMenu->value->Value;
		
		getOptions(selMenu);
	}
	
}


void Menu::incSelOpt()
{
	if (selOpt > 0)
	{
		selOpt--;
		draw::dd.optionsUIChanged = true;
	}
}

void Menu::decSelOpt()
{
	
	if (selOpt < currentMenu->subMenu->size() - 1)
	{
		selOpt++;
		draw::dd.optionsUIChanged = true;
	}
}

void Menu::changeValue(int val)
{
	menuItem* changedMenu = currentMenu->subMenu->at(selOpt);
	try 
	{
		//Exit if it has no value
		if (changedMenu->value->ID == MenuValueID::None) return;

		switch (changedMenu->value->Type)
		{
		case Menu::menuValueType::b:
			
			if (val == 1)
				changedMenu->value->Value = true;
			else if (val == -1)
				changedMenu->value->Value = false;

			break;
		case Menu::menuValueType::i:

			changedMenu->value->Value += val;
			
			break;

		case Menu::menuValueType::a:

			if (changedMenu->value->Value < changedMenu->value->ArrayValue.size()-1 && val == 1)
				changedMenu->value->Value++;
			else if (changedMenu->value->Value > 0 && val == -1)
				changedMenu->value->Value--;
			//page up/down
			else if (val == 100)
				changedMenu->value->Value = changedMenu->value->ArrayValue.size() - 1;
			else if (val == -100)
				changedMenu->value->Value = 0;

			break;
		}

		draw::dd.optionsUIChanged = true;
		getOptions(currentMenu->parent);
	}
	catch(std::exception ex)
	{ 
		std::cout << ex.what() << std::endl;
	}
}

//Patches elma with the new values
void Menu::saveSettings()
{
	for (std::pair<MenuValueID, int> option : optionList)
	{
		switch (option.first)
		{
		case MenuValueID::AppleCounter:
			Stats::stats.displayAppleCounter = option.second;
			break;
		case MenuValueID::DeathCounter:
			Stats::stats.displayDeathCounter = option.second;
			break;
		case MenuValueID::Invulnerability:
			Kuski::kus.toggleInvulnerability(option.second);
			break;
		case MenuValueID::SpeedHack:
			Kuski::kus.accelerationOfKuski((double)option.second);
			break;
		case MenuValueID::ChangeLGR:
			Level::lev.LGRselected = option.second;
			break;
		case MenuValueID::ShowGravity:
			Stats::stats.displayAppleGravity = option.second;
			break;
		case MenuValueID::ApplesTaken:
			Stats::stats.displayAppleTaken = option.second;
			break;
		}
	}

	Debug::debug.addDebugInfoItem(std::string("Saving settings..."));
}

/*
*	Enters the selected submenu.
*/
void Menu::enterSubMenu()
{
	
	if ( currentMenu->subMenu->at(selOpt)->subMenu->size() != 0)
	{
		subMenuLev++;
		currentMenu = currentMenu->subMenu->at(selOpt);
		selOpt = 0;
		draw::dd.optionsUIChanged = true;
	}
}

/*
*	Goes back by one menu if possible.
*/
void Menu::exitSubMenu()
{
	if (subMenuLev > 1)
	{
		subMenuLev--;
		selOpt = 0;
		currentMenu = currentMenu->parent;
		draw::dd.optionsUIChanged = true;
	}
}

