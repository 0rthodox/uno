#include "field.h"

std::string make_big(std::string & s) {
    for(auto & c : s)
        c = toupper(c);
    return s;
}

short determine_color(std::string & color_s) {
    if(color_s == "RED")
        return 0;
    else if(color_s == "YELLOW")
        return 1;
    else if(color_s == "GREEN")
        return 2;
    else if(color_s == "BLUE")
        return 3;
    else if(color_s == "BLACK")
        return 4;
    return -1;
}


field::field() : main_deck(), source_deck(), players() {
    reversed = false;

    if(!c_texture.loadFromFile("cards.png") || !bc_texture.loadFromFile("black_cards.png")) {
        std::cout << "No texture" << std::endl;
    }
    for(short i = 0; i < 2; ++i) {
        for(short color = 0; color < 4; ++color) {
            for(short number = 0; number <= 12; ++number)
                pack_of_cards.emplace_back(c_texture, color, number);
            for(short number = 13; number <= 14; ++number)
                pack_of_special.emplace_back(bc_texture, number, 4);
        }
    }
    std::list<card*> pack;
    for(auto & card : pack_of_cards)
        pack.push_back(&card);
    for(auto & card : pack_of_special)
        pack.push_back(&card);
    source_deck.set_cards(pack);
    source_deck.shuffle();
    short p_a, c_a;
    std::cout << "Please input the amount of cards given to each player" << std::endl;
    std::cout << "(It should not be bigger than 15)" << std::endl;
    while(1) {
    std::cin >> c_a;
    if (c_a <= 15)
        break;
    std::cout << "Sorry, but this is too big (like long long long int for GCC)" << std::endl;
    }
    std::cout << "Please input the amount of players and their names:" << std::endl;
    std::cin >> p_a;
    for (int i = 0; i < p_a; ++i) {
        std::string name;
        std::cin >> name;
        player new_player(name);
        new_player.transfer(source_deck, 0, c_a);
        players.push_back(new_player);
    }
    std::cout << "Starting a game with " << p_a << " players:" << std::endl;
    for(const auto & player : players)
        std::cout << player.get_name() << std::endl;
    curr_player = players.begin();
}

void field::draw() {
    field_window.create(sf::VideoMode(715, 214 * (curr_player->size() / 5 + 1) - 214 * (curr_player->size() == 15) + (244 * (!main_deck.empty()))), "FIELD", sf::Style::Titlebar);
    field_window.setPosition(sf::Vector2i(1100, 10));
    field_window.clear();
    if(!main_deck.empty()) {
        main_deck.top()->setPosition(572, 0);
        field_window.draw(main_deck.top()->get_sprite());
    }
    curr_player->output_cards(field_window, main_deck.empty());
    field_window.display();
}

void field::check_field() {
    if(main_deck.empty())
        std::cout << "Field is empty";
    else  {
        if(main_deck.top()->get_color() == 4)
            std::cout << *((special_card*)(main_deck.top()));
        else
            std::cout << *main_deck.top();
        std::cout << " on the field";
    }
    std::cout << std::endl << std::endl;
}

void field::take(short amount) {
    if (amount > (int)source_deck.size())
        amount = source_deck.size();
    if(amount + curr_player->size() > 15)
        amount = 15 - curr_player->size();
    curr_player->transfer(source_deck, 0, amount);
    curr_player->reset_special();
    draw();
}

bool field::put(short number, short color) {
    short new_active_color = 4;
    if (color == 4) {
        std::string new_active_color_s;
        while(1) {
            std::cin >> new_active_color_s;
            new_active_color_s = make_big(new_active_color_s);
            new_active_color = determine_color(new_active_color_s);
            if(new_active_color != -1)
                break;
            else
                std::cout << "Please input valid color" << std::endl;
        }
    }
    if(main_deck.empty() || (color == 4) || (number == main_deck.top()->get_number()) || (color == main_deck.top()->get_color()) || (main_deck.top()->get_color() == 4 && ((special_card*)(main_deck.top()))->get_active_color() == color)) {
        short num = curr_player->find(number, color, new_active_color);
        if(num >= 0) {
            main_deck.transfer(*curr_player, num);
            return true;
        }
    }
    return false;
}

void field::check() {
    std::cout << "Your cards:" << std::endl;
    std::cout << *curr_player << std::endl;
    draw();
}

void field::check_source() {
    std::cout << "Cards in the source deck: " << source_deck.size() << std::endl << std::endl;
}

void field::reshuffle() {
    source_deck.transfer(main_deck, 1, main_deck.size() - 1);
    source_deck.shuffle();
}

std::list<player>::iterator field::next_player() {
    if(curr_player == players.begin() && reversed)
        return --players.end();
    else if(curr_player == --players.end() && !reversed)
        return players.begin();
    else if(reversed) {
        auto res = curr_player;
        return --res;
    } else {
        auto res = curr_player;
        return ++res;
    }

}

void field::affect(const card * s_c) {
    short num = s_c->get_number();
    if (num == 10)
        curr_player = next_player();
    else if(num == 11)
        reversed = !reversed;
    else if(num == 12)
        next_player()->transfer(source_deck, 0 , 2);
    else if(num == 14)
        next_player()->transfer(source_deck, 0, 4);
    if(num == 12 || num == 14)
        curr_player = next_player();
}



void field::gameloop() {
    while (!curr_player->empty()) {
        system("pause");
        draw();
        system("cls");
        std::cout << curr_player->get_name() << ", it's Your turn!" << std::endl << std::endl;
        check_field();
        check_source();
        check();
        std::cout << "Please input your command // INFO to learn about the commands" << std::endl;
        std::string command;
        while(command != "PASS") {
            std::cin >> command;
            command = make_big(command);
            if(command == "INFO") {
                std::cout << "Available commands:" << std::endl;
                std::cout << "FIELD to look at field" << std::endl;
                std::cout << "CHECK to check your cards" << std::endl;
                std::cout << "TAKE 'n' to take some cards" << std::endl;
                std::cout << "PUT to put a card on the field" << std::endl;
                std::cout << "If card is black please add new color" << std::endl;
                std::cout << "SOURCE to count the cards available in the source deck" << std::endl;
                std::cout << "PASS to pass your turn" << std::endl;
                std::cout << "RESHUFFLE to reshuffle the main deck" << std::endl;
            }
            if(command == "FIELD")
                check_field();
            else if(command == "TAKE") {
                short amount;
                std::cin >> amount;
                take(amount);
            }
            else if(command == "PUT") {
                short color = 5, number = 15;
                std::string color_s, number_s;
                std::cin >> color_s;
                std::cin >> number_s;
                color_s = make_big(color_s);
                number_s = make_big(number_s);
                color = determine_color(color_s);
                if(number_s == "CHANGE") {
                    number = 13;
                    std::cin >> number_s;
                }
                else if(number_s == "PLUS") {
                    short number_2;
                    std::cin >> number_2;
                    if(number_2 == 2)
                        number = 12;
                    else if(number_2 == 4)
                        number = 14;
                }
                else if(number_s == "REVERSE")
                    number = 11;
                else if(number_s == "TURN") {
                    std::cin >> number_s;
                    number = 10;
                }
                else if(isdigit(number_s[0]))
                    number = std::stoi(number_s);
                if(put(number, color)) {
                    command = "PASS";
                    if(players.size() != 1)
                        affect(main_deck.top());
                }
            }
            else if(command == "CHECK")
                check();
            else if(command == "RESHUFFLE")
                reshuffle();
            else if(command == "SOURCE")
                check_source();
        }
        field_window.close();
        system("pause");
        system("cls");
        if(curr_player->empty()) {
            std::cout << "Player " << curr_player->get_name() << " won!" << std::endl;
            break;
        }
        else
            std::cout << "Pass the turn to next player, please" << std::endl;
        curr_player = next_player();
    }
}
