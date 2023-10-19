// item.hpp
#ifndef CURSED_ITEM_HPP_
#define CURSED_ITEM_HPP_
#include <vector>

class Item {
private:
	const int uid;

public:
	Item(int uid);

	int get_uid();
};

class Item_List {
private:
	std::vector<Item*> items;

public:
	void add_item(Item* item);

	bool remove_item(int uid);

	Item* get_item(int uid);
};

#endif
