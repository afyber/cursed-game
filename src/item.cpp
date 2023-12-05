// item.cpp
#include "item.hpp"

#include <vector>

using std::size_t;

// class Item

Item::Item(IUID iuid) : iuid(iuid) {}

unsigned int Item::get_uid() {
	return iuid;
}

// class Item_List

Item_List::~Item_List() {
	for (Item* p : items) {
		delete p;
	}
}

void Item_List::add_item(Item* item) {
	items.push_back(item);
}

Item* Item_List::pop_item(IUID uid) {
	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i]->get_uid() == uid) {
			Item* item = items[i];
			items.erase(items.begin() + i);
			return item;
		}
	}

	return nullptr;
}

Item* Item_List::get_item(IUID uid) {
	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i]->get_uid() == uid) {
			return items[i];
		}
	}

	return nullptr;
}
