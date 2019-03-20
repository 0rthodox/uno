#include "base_deck.h"

int rand_uns(int min, int max) {
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	static std::default_random_engine e(seed);
	std::uniform_int_distribution<int> d(min, max);
	return d(e);
}

base_deck::base_deck() {}

void base_deck::set_cards(std::list<card*> src) {
    cards.merge(src);
}

void base_deck::shuffle() {
    std::list<card*> shuffling_hand;
    shuffling_hand.splice(shuffling_hand.begin(), cards);
    while(shuffling_hand.size() > 0) {
        int delta = rand_uns(0, shuffling_hand.size() - 1);
        auto it = shuffling_hand.begin();
        advance(it, delta);
        cards.splice(cards.begin(), shuffling_hand, it);
    }
}

std::list<card*> base_deck::get_cards() {
    return cards;
}

void base_deck::transfer(base_deck & src, short start, short finish) {
    if (start >= 0 && start < finish && finish < (short)src.cards.size()) {
        auto it_b = src.cards.begin();
        auto it_e = it_b;
        std::advance(it_b, start);
        std::advance(it_e, finish);
        cards.splice(cards.begin(), src.cards, it_b, it_e);
    }
}
void base_deck::transfer(base_deck & src, short num) {
    if(num >= 0 && num < (short)src.cards.size()) {
        auto it = src.cards.begin();
        std::advance(it, num);
        cards.splice(cards.begin(), src.cards, it);
    }
}

std::ostream & operator<<(std::ostream & ostr, const base_deck & d) {
    for(auto it = d.cards.begin(); it != d.cards.end(); ++it) {
            if((**it).get_number() == 13 || (**it).get_number() == 14)
                ostr << *((special_card *)(*it)) << std::endl;
            else
                ostr << **it << std::endl;
    }

    return ostr;
}

bool base_deck::empty() const {
    return cards.empty();
}

size_t base_deck::size() const {
    return cards.size();
}

card * deck::top() const {
    return cards.front();
}
