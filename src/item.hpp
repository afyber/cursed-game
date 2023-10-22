// item.hpp
#ifndef CURSED_ITEM_HPP_
#define CURSED_ITEM_HPP_
#include <vector>

class Item {
private:
	const unsigned int uid;

public:
	Item(unsigned int uid);

	unsigned int get_uid();
};

class Item_List {
private:
	std::vector<Item*> items;

public:
	void add_item(Item* item);

	Item* pop_item(int uid);

	Item* get_item(int uid);
};

#endif
