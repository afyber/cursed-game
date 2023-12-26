// item.hpp
#ifndef CURSED_ITEM_HPP_
#define CURSED_ITEM_HPP_
#include <memory>
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
	std::vector<std::shared_ptr<Item>> items;

public:
	void add_item(std::shared_ptr<Item>);

	std::shared_ptr<Item> at(int index);

	std::shared_ptr<Item> pop(int index);

	std::vector<std::shared_ptr<Item>>::iterator begin();

	std::vector<std::shared_ptr<Item>>::iterator end();

	size_t size();
};

#endif
