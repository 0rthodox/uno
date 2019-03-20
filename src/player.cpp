#include "player.h"

player::player(const std::string & new_name) {
    name = new_name;
}

std::string player::get_name() const {
    return name;
}

short player::find(short number, short color, short new_active_color) {
    short res = 0;
    auto card = cards.begin();
    while(card != cards.end()) {
        if(number == (*card)->get_number() && (color == (*card)->get_color())) {
        if (new_active_color != 4)
            ((special_card*)(*card))->set_active(new_active_color);
            return res;
        }
        res++;
        card++;
    }
    return -1;
}

void player::output_cards(sf::RenderWindow & rw, bool main_deck_is_empty) {
    short i = 0;
    for(auto & card : cards) {
        if(main_deck_is_empty)
            card->setPosition(143 * (i % 5), 214 * (i / 5));
        else
            card->setPosition(143 * (i % 5), 30 + 214 * (1 + i / 5));
        rw.draw(card->get_sprite());
        ++i;
    }
}

void player::reset_special() {
    auto card = cards.begin();
    while(card != cards.end()) {
        if((*card)->get_number() == 4)
            ((special_card*)(*card))->set_active(4);
        ++card;
    }
}

