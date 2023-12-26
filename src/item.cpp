// item.cpp
#include "item.hpp"

// class Item

Item::Item(const char* name) : name(name) {}

const char* Item::get_name() {
	return name;
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
