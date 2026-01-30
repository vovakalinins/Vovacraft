#include <vector>
#include "world/data/items.h"

struct InventorySlot
{
    ItemData id = ItemData::None;
    int count = 0;
};

class Inventory
{
public:
    Inventory()
    {
        for (int i = 0; i < 36; i++)
            inventory[i] = {ItemData::None, 0};
    }

    bool addItem();

    InventorySlot &getSelectedSlot(int selection)
    {
        return inventory[selection];
    }

    InventorySlot &getSlot(int index)
    {
        return inventory[index];
    }
    // InventorySlot[34] getHotbar();
private:
    InventorySlot inventory[36];
};