// item.cpp
#include "item.hpp"

#include <vector>

// class Item

Item::Item(int uid) : uid(uid) {}

int Item::get_uid() {
	return uid;
}

// class Item_List

void Item_List::add_item(Item* item) {
	items.push_back(item);
}

Item* Item_List::pop_item(int uid) {
	Item* item = nullptr;

	for (int i = 0; i < items.size(); ++i) {
		if (items[i]->get_uid() == uid) {
			item = items[i];
			items.erase(items.begin() + i);
		}
	}

	return item;
}

Item* Item_List::get_item(int uid) {
	for (int i = 0; i < items.size(); ++i) {
		if (items[i]->get_uid() == uid) {
			return items[i];
		}
	}

	return nullptr;
}
