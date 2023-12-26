// item.cpp
#include "item.hpp"

// class Item

Item::Item(const char* name) : name(name) {}

const char* Item::get_name() {
	return name;
}

// class Item_List

void Item_List::add_item(Item* item) {
	items.push_back(item);
}

Item* Item_List::at(int index) {
	return items.at(index);
}

Item* Item_List::pop(int index) {
	Item* item = items.at(index);
	items.erase(items.begin() + index);
	return item;
}

std::vector<Item*>::iterator Item_List::begin() {
	return items.begin();
}

std::vector<Item*>::iterator Item_List::end() {
	return items.end();
}

size_t Item_List::size() {
	return items.size();
}
