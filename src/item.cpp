// item.cpp
#include "item.hpp"

// class Item

Item::Item(const char* name) : name(name) {}

Item::~Item() {}

const char* Item::get_name() {
	return name;
}

bool Item::can_wield() {
	return false;
}

Status Item::wield_status() {
	// Should never be reached for non-wieldable items
	throw std::logic_error("Attempted to get wield_status for non-wieldable item");
}

// class Weapon

Weapon::Weapon(const char* name, Status status) : status(status), Item(name) {}

bool Weapon::can_wield() {
	return true;
}

Status Weapon::wield_status() {
	return status;
}

// class Item_List

void Item_List::add_item(std::shared_ptr<Item> item) {
	items.push_back(item);
}

std::shared_ptr<Item> Item_List::at(int index) {
	return items.at(index);
}

std::shared_ptr<Item> Item_List::pop(int index) {
	std::shared_ptr<Item> item = items.at(index);
	items.erase(items.begin() + index);
	return item;
}

std::vector<std::shared_ptr<Item>>::iterator Item_List::begin() {
	return items.begin();
}

std::vector<std::shared_ptr<Item>>::iterator Item_List::end() {
	return items.end();
}

size_t Item_List::size() {
	return items.size();
}
