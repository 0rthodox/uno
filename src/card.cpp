#include "card.h"

card::card(const sf::Texture & src, const short & new_color = 0, const short & new_number = 0)
{
    if(new_color >=0 && new_color <= 4)
       color = new_color;
    if(new_number >= 0 && new_number <= 14)
        number = new_number;
    sprite.setTexture(src);
    if(number <= 12)
        sprite.setTextureRect(sf::IntRect(143 * number, 214 * color , 141.5, 214));
}

special_card::special_card(const sf::Texture & src, const short & new_number, const short & new_active_color = 4) : card::card(src, 4, new_number) {
    active_color = 4;
        sprite.setTextureRect(sf::IntRect(0, 214 * (number - 13) , 141.5, 214));

}

short card::get_color() const {
    return color;
}

short card::get_number() const {
    return number;
}

sf::Sprite card::get_sprite() const {
    return sprite;
}

void card::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

bool card::operator<(const card * c) {
    if(number == c->number)
        return (color < c->color);
    else
        return (number < c->number);
}

std::ostream & operator <<(std::ostream & ostr, const card  & c) {
    switch(c.color) {
        case 0 : ostr << "Red"; break;
        case 1 : ostr << "Yellow"; break;
        case 2 : ostr << "Green"; break;
        case 3 : ostr << "Blue"; break;
    }
    ostr << " ";
    if(c.number >= 0 && c.number < 10)
        ostr << c.number;
    else switch(c.number) {
        case 10 : ostr << "Turn Skip"; break;
        case 11 : ostr << "Reverse"; break;
        case 12 : ostr << "Plus 2"; break;
    }
    return ostr;
}

std::ostream & operator <<(std::ostream & ostr, const special_card & c) {
    ostr << "Black ";
    if(c.number == 13)
        ostr << "Change Color ";
    else if(c.number == 14)
        ostr << "Plus 4 ";
    switch(c.active_color) {
        case 0 : ostr << "Red"; break;
        case 1 : ostr << "Yellow"; break;
        case 2 : ostr << "Green"; break;
        case 3 : ostr << "Blue"; break;
    }
    return ostr;
}

void special_card::set_active(const short & new_color) {
    active_color = new_color;
}

short special_card::get_active_color() {
    return active_color;
}
