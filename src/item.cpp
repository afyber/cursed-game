// item.cpp
#include "item.hpp"

Item::Item(int uid) : uid(uid) {}

int Item::get_uid() {
	return uid;
}

void Item_List::add_item(Item* item) {
	items.push_back(item);
}

bool Item_List::remove_item(int uid) {
	for (int i = 0; i < items.size(); ++i) {
		if (items[i]->get_uid() == uid) {
			items.erase(items.begin() + i);
			return true;
		}
	}

	return false;
}

Item* Item_List::get_item(int uid) {
	for (int i = 0; i < items.size(); ++i) {
		if (items[i]->get_uid() == uid) {
			return items[i];
		}
	}

	return nullptr;
}
