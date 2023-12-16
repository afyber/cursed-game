// item.cpp
#include "item.hpp"

// class Item

Item::Item(IUID iuid) : iuid(iuid) {}

IUID Item::get_uid() {
	return iuid;
}

// class Item_List

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
	for (Item* item : items) {
		if (item->get_uid() == uid) {
			return item;
		}
	}

	return nullptr;
}

Item* Item_List::at(int index) {
	return items.at(index);
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
