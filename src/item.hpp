// item.hpp
#ifndef CURSED_ITEM_HPP_
#define CURSED_ITEM_HPP_
#include <vector>

#include "definitions.hpp"

class Item {
private:
	const char* name;

public:
	Item(const char* name);

	const char* get_name();
};

class Item_List {
private:
	std::vector<Item*> items;

public:
	void add_item(Item* item);

	Item* at(int index);

	Item* pop(int index);

	std::vector<Item*>::iterator begin();

	std::vector<Item*>::iterator end();

	size_t size();
};

#endif
