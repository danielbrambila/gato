#ifndef TABLERO_HPP
#define TABLERO_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

class Tablero {
public:
    Tablero() {
        for (auto& row : casillas) {
            row.fill(' ');
        }

        if (!fondoTexture.loadFromFile("fondo.jpeg")) {
            std::cerr << "Error al cargar la imagen de fondo fondo.jpeg" << std::endl;
        }
        fondoSprite.setTexture(fondoTexture);
    }

    bool marcarCasilla(int row, int col, char simbolo) {
        if (casillas[row][col] == ' ') {
            casillas[row][col] = simbolo;
            return true;
        }
        return false;
    }

    bool verificarVictoria(char simbolo) {
        // Verificar filas, columnas y diagonales
        for (int i = 0; i < 3; ++i) {
            if (casillas[i][0] == simbolo && casillas[i][1] == simbolo && casillas[i][2] == simbolo)
                return true;
            if (casillas[0][i] == simbolo && casillas[1][i] == simbolo && casillas[2][i] == simbolo)
                return true;
        }
        if (casillas[0][0] == simbolo && casillas[1][1] == simbolo && casillas[2][2] == simbolo)
            return true;
        if (casillas[0][2] == simbolo && casillas[1][1] == simbolo && casillas[2][0] == simbolo)
            return true;
        return false;
    }

    void dibujar(sf::RenderWindow& window) {
        window.draw(fondoSprite);

        sf::RectangleShape line(sf::Vector2f(600, 5));
        line.setFillColor(sf::Color::Black);

        for (int i = 1; i < 3; ++i) {
            line.setPosition(0, i * 200);
            window.draw(line);
            line.setRotation(90);
            line.setPosition(i * 200, 0);
            window.draw(line);
            line.setRotation(0);
        }

        sf::Font font;
        if (!font.loadFromFile("Arial.ttf")) {
            // Manejar el error si la fuente no se carga
            std::cerr << "Error al cargar la fuente Arial.ttf" << std::endl;
            return;
        }
        sf::Text text("", font, 100);
        text.setFillColor(sf::Color::Black);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (casillas[i][j] != ' ') {
                    text.setString(casillas[i][j]);
                    text.setPosition(j * 200 + 50, i * 200 + 50);
                    window.draw(text);
                }
            }
        }
    }

private:
    std::array<std::array<char, 3>, 3> casillas;
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;
};

#endif // TABLERO_HPP