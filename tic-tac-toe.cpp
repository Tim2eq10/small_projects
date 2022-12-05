//============================================================================
// Source : tic-tac-toe.cpp
// Author : Poletaev Timur
// Description : Tic-Tac-Toe game for two players using SFML.
//============================================================================
#include <iostream>

#include "SFML/Graphics.hpp"
//============================================================================
class TicTacToe {
    char field[3][3];
    char X = 'X';
    char O = 'O';
    char EMPTY = ' ';
    char turn = X;
    bool is_bot_turn = rand() % 2;

    char opposite(char turn) {
        return (turn == X ? O : X);
    }
    bool is_win(char turn_symb) {
        return
            field[0][0] == field[0][1] && field[0][1] == field[0][2] && field[0][2] == turn_symb ||
            field[1][0] == field[1][1] && field[1][1] == field[1][2] && field[1][2] == turn_symb ||
            field[2][0] == field[2][1] && field[2][1] == field[2][2] && field[2][2] == turn_symb ||
            field[0][0] == field[1][0] && field[1][0] == field[2][0] && field[2][0] == turn_symb ||
            field[0][1] == field[1][1] && field[1][1] == field[2][1] && field[2][1] == turn_symb ||
            field[0][2] == field[1][2] && field[1][2] == field[2][2] && field[2][2] == turn_symb ||
            field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[2][2] == turn_symb ||
            field[0][2] == field[1][1] && field[1][1] == field[2][0] && field[2][0] == turn_symb;
    }
    bool is_draw() {
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                if (field[i][j] == EMPTY)
                    return false;
        return true;
    }
    bool is_finished() {
        return is_draw() || is_win(X) || is_win(O);
    }
public:
    TicTacToe() {
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                field[i][j] = EMPTY;
            }
        }
    }

    void perform_move(size_t i, size_t j) {
        //if (!is_bot_turn && !is_finished() && field[i][j] == EMPTY) {
        if (!is_finished() && field[i][j] == EMPTY) {
            field[i][j] = turn;
            turn = opposite(turn);
            is_bot_turn = !is_bot_turn;
        }
    }
    
    void draw(sf::RenderWindow& window) {
        sf::RectangleShape a({ 300, 300 });
        a.setFillColor(sf::Color::White);
        window.draw(a);

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                a.setPosition({ 300.f * i, 300.f * j });
                window.draw(a);
                if (field[i][j] == O) {
                    sf::CircleShape O(100);
                    O.setFillColor(sf::Color::White);
                    O.setOutlineThickness(5);
                    O.setOutlineColor(sf::Color::Black);
                    O.setPosition({ 300.f * i + 50, 300.f * j + 50 });
                    window.draw(O);
                }
                else if (field[i][j] == X) {
                    sf::Vertex line1[2]{
                        sf::Vertex({ 300.f * i + 50, 300.f * j + 50 }),
                        sf::Vertex({ 300.f * (i + 1) - 50, 300.f * (j + 1) - 50 })
                    };
                    sf::Vertex line2[2]{
                        sf::Vertex({ 300.f * i + 50, 300.f * (j + 1) - 50 }),
                        sf::Vertex({ 300.f * (i + 1) - 50, 300.f * j + 50 })
                    };
                    for (int i = 0; i < 2; i++) {
                        line1[i].color = sf::Color::Black;
                        line2[i].color = sf::Color::Black;
                    }
                    for (int i = -2; i <= 2; i++) {
                        window.draw(line1, 2, sf::Lines);
                        window.draw(line2, 2, sf::Lines);
                        for (int i = 0; i < 2; i++) {
                            line1[i].position.x++;
                            line2[i].position.x++;
                        }
                    }
                }
            }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "The name of the ship was the billy of tea");

    TicTacToe game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);

                int _i = pos.x / 300;
                int _j = pos.y / 300;
                game.perform_move(_i, _j);

                while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {};
            }


            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        game.draw(window);

        window.display();
    }
}
//============================================================================
