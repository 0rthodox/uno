#ifndef FIELD_H
#define FIELD_H

#include "player.h"

std::string make_big(std::string & s);

short determine_color(std::string & color);

class field {
    sf::RenderWindow field_window;
    sf::Texture c_texture, bc_texture;
    std::list<card> pack_of_cards;
    std::list<special_card> pack_of_special;
    deck main_deck;
    deck source_deck;
    std::list<player> players;
    bool reversed;
    std::list<player>::iterator curr_player;
    void draw();
    void check_field();
    void show();
    void take(short amount);
    bool put(short number, short color);
    void check();
    std::list<player>::iterator next_player();
    void affect(const card * s_c);
    void reshuffle();
    void check_source();
    std::string new_window();
public:
    field();
    void gameloop();
};

#endif // FIELD_H
