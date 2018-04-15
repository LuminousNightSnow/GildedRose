#ifndef CPP_ITEM_H
#define CPP_ITEM_H

#include <string>


class Item
{
public:
    std::string name;
    int days_remaining;
    int quality;

    Item(std::string name, int days_remaining, int quality)
            : name(std::move(name)), days_remaining(days_remaining), quality(quality)
    {
    }

    virtual void update() = 0;

    virtual ~Item() = default;
};


class NormalItem : public Item
{
public:
    NormalItem(const std::string& name, int days_remaining, int quality) : Item(name, days_remaining, quality){};
    void update() override;
};

class AgedBrieItem : public Item
{
public:
    AgedBrieItem(const std::string& name, int days_remaining, int quality) : Item(name, days_remaining, quality){};

    void update() override;
};

class SulfurasItem : public Item
{
public:
    SulfurasItem(std::string name, int days_remaining, int quality) : Item(name, days_remaining, quality){};

    void update() override;
};

class BackstageItem : public Item
{
public:
    BackstageItem(std::string name, int days_remaining, int quality) : Item(name, days_remaining, quality) {}

    void update() override;
};


#endif //CPP_ITEM_H
