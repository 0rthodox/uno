#ifndef PLAYER_H
#define PLAYER_H

#include "base_deck.h"

class player : public base_deck
{
    public:
        player(const std::string & new_name);
        std::string get_name() const;
        short find(short number, short color, short new_active_color);
        void reset_special();
        void output_cards(sf::RenderWindow & rw, bool is_empty);
        void new_output(sf::RenderWindow & rw, sf::Vector2u position, std::vector<std::list<card*>::iterator> & displayed);
        short check_mouse(const sf::Vector2i & m_coord);
    protected:

    private:
        std::string name;
};

#endif // PLAYER_H
