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
		

	//Display Options
	newsubMenuItem = createMenuItem(mainMenuItem, MenuItemsID::DisplayOptions, std::string("Display Options"));
	//Display Options submenus
	createMenuItem(newsubMenuItem, MenuItemsID::AppleCounter, std::string("Apple Counter"), MenuValueID::AppleCounter, menuValueType::b, true);
	createMenuItem(newsubMenuItem, MenuItemsID::DeathCounter, std::string("Finish/Death Counter"), MenuValueID::DeathCounter, menuValueType::b, true);
	createMenuItem(newsubMenuItem, MenuItemsID::ShowGravity, std::string("Apple Gravity"), MenuValueID::ShowGravity, menuValueType::b, true);
	createMenuItem(newsubMenuItem, MenuItemsID::TimeAppleTaken, std::string("Time of Apples Taken"), MenuValueID::TimeAppleTaken, menuValueType::a, Stats::stats.timeAppleTakenValue, Stats::stats.timeAppleTakenList);
	createMenuItem(newsubMenuItem, MenuItemsID::LineToObject, std::string("Arrows to Objects"), MenuValueID::LineToObject, menuValueType::a, Objects::obj.arrowObjectValue, Objects::obj.arrowObjectList);
	createMenuItem(newsubMenuItem, MenuItemsID::ShadowKuski, std::string("Shadow Kuski"), MenuValueID::ShadowKuski, menuValueType::a, Kuski::kus.shadowKuskiValue, Kuski::kus.shadowKuskiList);
	createMenuItem(newsubMenuItem, MenuItemsID::ChatTimestamp, std::string("Chat Timestamp"), MenuValueID::ChatTimestamp, menuValueType::a, System::sys.chatTimestampValue, System::sys.chatTimestampList);


	//General options
	newsubMenuItem = createMenuItem(mainMenuItem, MenuItemsID::GeneralOptions, std::string("General Options"));
	//General options submenus
	createMenuItem(newsubMenuItem, MenuItemsID::ChangeLGR, std::string("Change LGR"), MenuValueID::ChangeLGR, menuValueType::a, Level::lev.LGRselected, Level::lev.LGRlist);
	createMenuItem(newsubMenuItem, MenuItemsID::DeathDelay, std::string("Change Death Delay (MS)"), MenuValueID::DeathDelay, menuValueType::i, 1000, {}, range(0, 1000));


	//What if (offline hacks)
	newsubMenuItem = createMenuItem(mainMenuItem, MenuItemsID::WhatIfs, std::string("What If..."));
	//What ifs... submenus
	createMenuItem(newsubMenuItem, MenuItemsID::Invulnerability, std::string("Invulnerability"), MenuValueID::Invulnerability, menuValueType::a, Kuski::kus.invulnerabilityValue, Kuski::kus.invulnerabilityList);
	createMenuItem(newsubMenuItem, MenuItemsID::SpeedHack, std::string("Speed Hack"), MenuValueID::SpeedHack, menuValueType::i, 600, {}, range(0, 2500));



	//display the main menu when first opening
	getOptions(currentMenu);

	
}

Menu::menuItem* Menu::createMenuItem(menuItem* parent, MenuItemsID itemsID, std::string Name, MenuValueID valueID, menuValueType Type, int Value, std::vector<std::string> arrayVal, range r )
{
	
	menuItem* newMenuItem = new menuItem;
	menuValue* newmenuValue = new menuValue;

	//create the menu value
	newmenuValue->ID = valueID;
	newmenuValue->Type = Type;
	newmenuValue->Name = Name + std::string("Val");
	newmenuValue->Value = Value;
	newmenuValue->ArrayValue = arrayVal;
	newmenuValue->Range = r;

	//create the menu
	newMenuItem->ID = itemsID;
	newMenuItem->Name = Name;
	newMenuItem->subMenu = new std::vector<menuItem*>; //Add submenus after creating the parent menu.
	newMenuItem->parent = parent;
	newMenuItem->value = newmenuValue;

	if (parent != NULL)
		parent->subMenu->push_back(newMenuItem);

	return newMenuItem;
}

//Displays the current menu item
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

//go to the next menu
void Menu::incSelOpt()
{
	if (selOpt > 0)
	{
		selOpt--;
		draw::dd.optionsUIChanged = true;
	}
}

//go to the previous menu
void Menu::decSelOpt()
{
	
	if (selOpt < currentMenu->subMenu->size() - 1)
	{
		selOpt++;
		draw::dd.optionsUIChanged = true;
	}
}

//Change the value of the current menu item.
void Menu::changeValue(int val)
{
	menuItem* changedMenu = currentMenu->subMenu->at(selOpt);
	
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

		//default no ranges
		if (changedMenu->value->Range.min == 0 && changedMenu->value->Range.max == 0)
		{
			changedMenu->value->Value += val;
			break;
		}

		//check if the value is not bigger or smaller than the ranges
		if (changedMenu->value->Range.min < (changedMenu->value->Value + val) && changedMenu->value->Range.max >(changedMenu->value->Value + val))
			changedMenu->value->Value += val;
		else if(val > 0)
			changedMenu->value->Value = changedMenu->value->Range.max;
		else if (val < 0)
			changedMenu->value->Value = changedMenu->value->Range.min;

		break;

	case Menu::menuValueType::a:

		if (changedMenu->value->Value < changedMenu->value->ArrayValue.size() - 1 && val == 1) //left arrow key
			changedMenu->value->Value++;
		else if (val == 1) //roll back
			changedMenu->value->Value = 0;
		else if (changedMenu->value->Value > 0 && val == -1) //right arrow key
			changedMenu->value->Value--;
		else if (val == -1) //roll back other way
			changedMenu->value->Value  = changedMenu->value->ArrayValue.size() - 1;

		//page up/down go to last/first
		else if (val == 100)
			changedMenu->value->Value = changedMenu->value->ArrayValue.size() - 1;
		else if (val == -100)
			changedMenu->value->Value = 0;

		break;
	}

	draw::dd.optionsUIChanged = true;
	getOptions(currentMenu->parent);

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
			Level::lev.LGRchanged = true;
			break;
		case MenuValueID::ShowGravity:
			Stats::stats.displayAppleGravity = option.second;
			break;
		case MenuValueID::TimeAppleTaken:
			Stats::stats.timeAppleTakenValue = option.second;
			break;
		case MenuValueID::DeathDelay:
			Kuski::kus.setDeathDelay(option.second);
			break;
		case MenuValueID::LineToObject:
			Objects::obj.arrowObjectValue = option.second;
			break;
		case MenuValueID::ShadowKuski:
			Kuski::kus.shadowKuskiValue = option.second;
			break;
		case MenuValueID::ChatTimestamp:
			System::sys.chatTimestampValue = option.second;
			break;
		}
	}

	Debug::debug.addDebugInfoItem(std::string("Saving settings..."));
}


//Enters the selected submenu.
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

//Goes back by one menu if possible.
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

