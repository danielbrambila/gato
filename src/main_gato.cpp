#include <SFML/Graphics.hpp>
#include <vector>

class Jugador {
public:
    Jugador(sf::RenderWindow& ventana);
    void moverDerecha();
    void moverIzquierda();
    void dibujar(sf::RenderWindow& ventana);
    void escalarPaleta();
    void restaurarEscala();
    sf::FloatRect getPosition();
private:
    sf::RectangleShape paleta;
};

Jugador::Jugador(sf::RenderWindow& ventana) {
    paleta.setSize(sf::Vector2f(100, 20));
    paleta.setFillColor(sf::Color::Red);
    paleta.setPosition(ventana.getSize().x / 2 - paleta.getSize().x / 2, ventana.getSize().y - 50);
}

void Jugador::moverDerecha() {
    paleta.move(10, 0);
}

void Jugador::moverIzquierda() {
    paleta.move(-10, 0);
}

void Jugador::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(paleta);
}

void Jugador::escalarPaleta() {
    paleta.setScale(1.5f, 1.0f);
}

void Jugador::restaurarEscala() {
    paleta.setScale(1.0f, 1.0f);
}

sf::FloatRect Jugador::getPosition() {
    return paleta.getGlobalBounds();
}

class Puntuaje {
public:
    Puntuaje();
    void incrementarPuntuacion(int puntos);
    void reiniciarPuntuacion();
    void draw(sf::RenderWindow& window);
private:
    int puntuacion;
    sf::Text textoPuntuacion;
    sf::Font fuente;
};

Puntuaje::Puntuaje() : puntuacion(0) {
    fuente.loadFromFile("ruta/a/tu/fuente.ttf");
    textoPuntuacion.setFont(fuente);
    textoPuntuacion.setCharacterSize(30);
    textoPuntuacion.setFillColor(sf::Color::Black);
    textoPuntuacion.setPosition(10, 10);
    textoPuntuacion.setString("Puntuacion: 0");
}

void Puntuaje::incrementarPuntuacion(int puntos) {
    puntuacion += puntos;
    textoPuntuacion.setString("Puntuacion: " + std::to_string(puntuacion));
}

void Puntuaje::reiniciarPuntuacion() {
    puntuacion = 0;
    textoPuntuacion.setString("Puntuacion: 0");
}

void Puntuaje::draw(sf::RenderWindow& window) {
    window.draw(textoPuntuacion);
}

class Tablero {
public:
    Tablero();
    void dibujar(sf::RenderWindow& ventana);
    bool marcarCasilla(int fila, int columna, char jugador);
    char comprobarGanador();
    bool estaLleno();

private:
    std::vector<std::vector<char>> casillas;
    sf::RectangleShape lineas[4];
    sf::Font fuente;
    sf::Text textoCasillas[3][3];
};

Tablero::Tablero() : casillas(3, std::vector<char>(3, ' ')) {
    for (int i = 0; i < 4; ++i) {
        lineas[i].setFillColor(sf::Color::Black);
    }
    lineas[0].setSize(sf::Vector2f(600, 5));
    lineas[0].setPosition(0, 200);
    lineas[1].setSize(sf::Vector2f(600, 5));
    lineas[1].setPosition(0, 400);
    lineas[2].setSize(sf::Vector2f(5, 600));
    lineas[2].setPosition(200, 0);
    lineas[3].setSize(sf::Vector2f(5, 600));
    lineas[3].setPosition(400, 0);

    fuente.loadFromFile("ruta/a/tu/fuente.ttf");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            textoCasillas[i][j].setFont(fuente);
            textoCasillas[i][j].setCharacterSize(100);
            textoCasillas[i][j].setFillColor(sf::Color::Black);
            textoCasillas[i][j].setPosition(j * 200 + 50, i * 200 + 50);
        }
    }
}

void Tablero::dibujar(sf::RenderWindow& ventana) {
    for (int i = 0; i < 4; ++i) {
        ventana.draw(lineas[i]);
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            textoCasillas[i][j].setString(casillas[i][j]);
            ventana.draw(textoCasillas[i][j]);
        }
    }
}

bool Tablero::marcarCasilla(int fila, int columna, char jugador) {
    if (casillas[fila][columna] == ' ') {
        casillas[fila][columna] = jugador;
        return true;
    }
    return false;
}

char Tablero::comprobarGanador() {
    for (int i = 0; i < 3; ++i) {
        if (casillas[i][0] == casillas[i][1] && casillas[i][1] == casillas[i][2] && casillas[i][0] != ' ') {
            return casillas[i][0];
        }
        if (casillas[0][i] == casillas[1][i] && casillas[1][i] == casillas[2][i] && casillas[0][i] != ' ') {
            return casillas[0][i];
        }
    }
    if (casillas[0][0] == casillas[1][1] && casillas[1][1] == casillas[2][2] && casillas[0][0] != ' ') {
        return casillas[0][0];
    }
    if (casillas[0][2] == casillas[1][1] && casillas[1][1] == casillas[2][0] && casillas[0][2] != ' ') {
        return casillas[0][2];
    }
    return ' ';
}

bool Tablero::estaLleno() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (casillas[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

class Juego {
public:
    Juego();
    void ejecutar();

private:
    sf::RenderWindow ventana;
    Tablero tablero;
    char turno;
    bool juegoTerminado;
    sf::Font fuente;
    sf::Text textoEstado;

    void procesarEventos();
    void actualizar();
    void renderizar();
};

Juego::Juego() : ventana(sf::VideoMode(600, 600), "Tres en Raya"), turno('X'), juegoTerminado(false) {
    fuente.loadFromFile("ruta/a/tu/fuente.ttf");
    textoEstado.setFont(fuente);
    textoEstado.setCharacterSize(50);
    textoEstado.setFillColor(sf::Color::Black);
    textoEstado.setPosition(10, 10);
}

void Juego::ejecutar() {
    while (ventana.isOpen()) {
        procesarEventos();
        actualizar();
        renderizar();
    }
}

void Juego::procesarEventos() {
    sf::Event evento;
    while (ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            ventana.close();
        }
        if (evento.type == sf::Event::MouseButtonPressed && !juegoTerminado) {
            int fila = evento.mouseButton.y / 200;
            int columna = evento.mouseButton.x / 200;
            if (tablero.marcarCasilla(fila, columna, turno)) {
                turno = (turno == 'X') ? 'O' : 'X';
            }
        }
    }
}

void Juego::actualizar() {
    char ganador = tablero.comprobarGanador();
    if (ganador != ' ') {
        textoEstado.setString(std::string("Ganador: ") + ganador);
        juegoTerminado = true;
    } else if (tablero.estaLleno()) {
        textoEstado.setString("Empate");
        juegoTerminado = true;
    } else {
        textoEstado.setString(std::string("Turno: ") + turno);
    }
}

void Juego::renderizar() {
    ventana.clear(sf::Color::White);
    tablero.dibujar(ventana);
    ventana.draw(textoEstado);
    ventana.display();
}

int main() {
    Juego juego;
    juego.ejecutar();
    return 0;
}