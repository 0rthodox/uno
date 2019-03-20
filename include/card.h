#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class player;

class card {
public:
    card();
    card(const sf::Texture & src, const short & new_color, const short & new_number);
    short get_color() const;
    short get_number() const;
    sf::Sprite get_sprite() const;
    friend std::ostream & operator << (std::ostream & ostr, const card & c);
    bool operator<(const card * c);
    void setPosition(float x, float y);

protected:
    short number;
    short color;
    sf::Sprite sprite;

private:

};

class special_card : public card {
    short active_color;
public:
    short get_active_color();
    friend std::ostream & operator << (std::ostream & ostr, const special_card & c);
    void set_active(const short & new_color);
    special_card(const sf::Texture & src, const short & new_number, const short & new_active_color);
};

#endif // CARD_H
