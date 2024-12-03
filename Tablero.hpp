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

    bool estaLleno() const {
        for (const auto& row : casillas) {
            for (char casilla : row) {
                if (casilla == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    void dibujar(sf::RenderWindow& window) const {
        window.draw(fondoSprite);
        // Aquí puedes agregar el código para dibujar las casillas y los símbolos
    }

    bool verificarVictoria(char simbolo) const {
        // Aquí puedes agregar el código para verificar si hay una victoria
        return false;
    }

private:
    std::array<std::array<char, 3>, 3> casillas;
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;
};

#endif // TABLERO_HPP