#ifndef BASE_DECK_H
#define BASE_DECK_H

#include "card.h"
#include <list>
#include <random>
#include <chrono>

int rand_uns(int min, int max);

class base_deck
{
public:
    base_deck();
    void shuffle();
    friend std::ostream & operator<<(std::ostream & ostr, const base_deck & d);
    void sort();
    void transfer(base_deck & src, short start, short finish);
    void transfer(base_deck & src, short num);
    std::list<card*> get_cards();
    void set_cards(std::list<card*> src);
    bool empty() const;
    size_t size() const;


protected:
    std::list<card*> cards;

private:
};

class deck : public base_deck {
public:
    deck() : base_deck() {}
    card * top() const ;
};

#endif // BASE_DECK_H
