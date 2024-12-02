#ifndef JUGADOR_HPP
#define JUGADOR_HPP

class Jugador {
public:
    Jugador(char simbolo) : simbolo(simbolo) {}
    char getSimbolo() const { return simbolo; }

private:
    char simbolo;
};

#endif // JUGADOR_HPP