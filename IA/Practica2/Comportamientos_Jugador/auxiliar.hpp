#ifndef COMPORTAMIENTOAUXILIAR_H
#define COMPORTAMIENTOAUXILIAR_H

#include "comportamientos/comportamiento.hpp"
#include <boost/functional/hash.hpp>
#include <functional>
#include <optional>
#include <time.h>
#include <unordered_set>
#include <vector>

struct EstadoAux {
    int fila;
    int col;
    int brujula;
    bool zapatillas;

    bool operator==(const EstadoAux &rhs) const {
        return fila == rhs.fila && col == rhs.col && brujula == rhs.brujula &&
               zapatillas == rhs.zapatillas;
    }

    bool operator<(const EstadoAux &other) const {
        return std::tie(fila, col, brujula, zapatillas) <
               std::tie(other.fila, other.col, other.brujula, other.zapatillas);
    }
};

template <> struct std::hash<EstadoAux> {
    std::size_t operator()(const EstadoAux &e) const {
        return ((e.fila * 73856093) ^ (e.col * 19349663) ^ (e.brujula * 83492791) ^
                (e.zapatillas ? 1 : 0));
    }
};

struct NodoAux {
    EstadoAux estado;
    std::vector<Action> secuencia;
    unsigned int coste;

    NodoAux(const EstadoAux &e, std::vector<Action> s, int c)
        : estado(e), secuencia(std::move(s)), coste(c) {}

    bool operator<(const NodoAux &other) const {
        if (coste != other.coste)
            return coste < other.coste;
        return estado < other.estado;
    }
};

class ComportamientoAuxiliar : public Comportamiento {

  public:
    ComportamientoAuxiliar(unsigned int size = 0)
        : Comportamiento(size), giro45izq(0), tiene_zapatillas(false), decision(0),
          giro_prueba(true), hay_plan(false), recargando(false), continua_recargando(false),
          ciclos(size, std::vector<unsigned short>(size, 0)) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < 3; ++j) {
                mapaResultado[i][j] = 'P';
                mapaResultado[i][size - 1 - j] = 'P';
                mapaResultado[j][i] = 'P';
                mapaResultado[size - 1 - j][i] = 'P';

                mapaCotas[i][j] = 0;
                mapaCotas[i][size - 1 - j] = 0;
                mapaCotas[j][i] = 0;
                mapaCotas[size - 1 - j][i] = 0;
            }
        }
    }

    ComportamientoAuxiliar(std::vector<std::vector<unsigned char>> mapaR,
                           std::vector<std::vector<unsigned char>> mapaC)
        : Comportamiento(mapaR, mapaC), hay_plan(false), tiene_zapatillas(false) {
        // Inicializar Variables de Estado Niveles 2,3
    }

    ComportamientoAuxiliar(const ComportamientoAuxiliar &comport) : Comportamiento(comport) {}

    ~ComportamientoAuxiliar() {}

    Action think(Sensores sensores);

    int interact(Action accion, int valor);

  private:
    /*  ╔═════════════════════════════════════════════════╗
        ║               Variables de Estado               ║
        ╚═════════════════════════════════════════════════╝ */

    int giro45izq;
    bool tiene_zapatillas;
    bool giro_prueba;
    int decision;
    std::vector<std::vector<unsigned short>> ciclos;

    // Nivel 3
    bool hay_plan;
    std::vector<Action> plan;

    // Nivel 4
    bool recargando;
    bool continua_recargando;
    int destRecargaF{0};
    int destRecargaC{0};
    /*  ╔═════════════════════════════════════════════════╗
        ║                 Métodos genéricos               ║
        ╚═════════════════════════════════════════════════╝ */

    constexpr inline auto getVisionPosition(int playerF, int playerC, Orientacion orientacion,
                                            int visionIndex) const -> std::pair<int, int>;

    void cartografiar(Sensores &sensores);

    auto
    decidirAccion(size_t pos, const Sensores &sensores,
                  std::function<bool(unsigned char, const Sensores &, unsigned)> esTransitableFunc)
        -> std::optional<Action>;

    inline auto viablePorAltura(int dif) const -> bool;

    template <int Nivel>
    inline bool esTransitable(unsigned char celda, const Sensores &sensores, unsigned pos,
                              bool tiene_zap = false) const noexcept;

    auto ComportamientoAuxiliarNivel_0(Sensores &sensores) noexcept -> Action;
    auto ComportamientoAuxiliarNivel_1(Sensores &sensores) noexcept -> Action;
    auto ComportamientoAuxiliarNivel_2(Sensores &sensores) noexcept -> Action;
    auto ComportamientoAuxiliarNivel_3(Sensores &sensores) noexcept -> Action;
    auto ComportamientoAuxiliarNivel_4(Sensores &sensores) noexcept -> Action;

    /*  ╔═════════════════════════════════════════════════╗
        ║                 Métodos nivel 0                 ║
        ╚═════════════════════════════════════════════════╝ */

    auto casillasInteresantes(Sensores &sensores) const noexcept -> std::vector<size_t>;

    /*  ╔═════════════════════════════════════════════════╗
        ║                 Métodos nivel 1                 ║
        ╚═════════════════════════════════════════════════╝ */

    auto casillasCartografia(Sensores &sensores) const -> std::vector<size_t>;

    /*  ╔═════════════════════════════════════════════════╗
        ║                 Métodos nivel 3                 ║
        ╚═════════════════════════════════════════════════╝ */

    void anularMatriz(std::vector<std::vector<unsigned char>> &matriz) noexcept;

    template <int Nivel>
    auto calcularCoste(Action accion, const EstadoAux &st) const noexcept -> int;

    void visualizaPlan(const EstadoAux &st, const std::vector<Action> &plan) noexcept;

    template <int Nivel>
    auto auxiliarAestrella(const EstadoAux &inicio, const EstadoAux &final) noexcept
        -> std::vector<Action>;

    auto applyAction(Action accion, const EstadoAux &st) noexcept -> EstadoAux;

    auto casillaAccesibleAuxiliar(const EstadoAux &st, Action accion) noexcept -> bool;

    /*  ╔═════════════════════════════════════════════════╗
        ║                 Métodos nivel 4                 ║
        ╚═════════════════════════════════════════════════╝ */

    auto auxiliarADesconocido(
        const EstadoAux &inicio, const EstadoAux &final,
        const std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> &evitar)
        -> std::vector<Action>;

    auto explorarDesconocido(const EstadoAux &inicio) -> std::vector<Action>;
};

#endif
