// item.hpp
#ifndef CURSED_ITEM_HPP_
#define CURSED_ITEM_HPP_
#include <vector>

#include "definitions.hpp"

typedef unsigned long long int IUID;

class Item {
private:
	const IUID iuid;

public:
	Item(IUID iuid);

	IUID get_uid();
};

class Item_List {
private:
	std::vector<Item*> items;

public:
	void add_item(Item* item);

	Item* pop_item(IUID iuid);

	Item* get_item(IUID iuid);

	Item* at(int index);

	std::vector<Item*>::iterator begin();

	std::vector<Item*>::iterator end();

	size_t size();
};

#endif
