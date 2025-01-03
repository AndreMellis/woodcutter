#ifndef INVENTORY_HEADER_
#define INVENTORY_HEADER_

struct Inventory
{
    int wood;
    int totalEmployees;
    int idleEmployees;
    int money;
    int day; // 1-7, Sun-Mon
};


enum class ItemTypes
{
    INSERT_ITEM_HERE
};

struct InventoryItem
{
    ItemTypes eItemType;
    int iItemCount;
};

#endif