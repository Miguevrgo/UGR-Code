#ifndef COMPORTAMIENTORESCATADOR_H
#define COMPORTAMIENTORESCATADOR_H

#include "comportamientos/comportamiento.hpp"
#include <boost/functional/hash.hpp>
#include <cstddef>
#include <deque>
#include <functional>
#include <optional>
#include <time.h>
#include <unordered_set>
#include <utility>
#include <vector>

struct EstadoRes {
    int fila;
    int col;
    int brujula;
    bool zapatillas;

    bool operator==(const EstadoRes &rhs) const {
        return fila == rhs.fila && col == rhs.col && brujula == rhs.brujula &&
               zapatillas == rhs.zapatillas;
    }

    bool operator<(const EstadoRes &other) const {
        return std::tie(fila, col, brujula, zapatillas) <
               std::tie(other.fila, other.col, other.brujula, other.zapatillas);
    }
};

template <> struct std::hash<EstadoRes> {
    std::size_t operator()(const EstadoRes &e) const {
        return ((e.fila * 73856093) ^ (e.col * 19349663) ^ (e.brujula * 83492791) ^
                (e.zapatillas ? 1 : 0));
    }
};

struct NodoDijkstra {
    EstadoRes estado;
    std::vector<Action> secuencia;
    int coste;

    NodoDijkstra(const EstadoRes &e, std::vector<Action> s, int c)
        : estado(e), secuencia(std::move(s)), coste(c) {}

    bool operator<(const NodoDijkstra &other) const {
        if (coste != other.coste)
            return coste < other.coste;
        return estado < other.estado;
    }
};

class ComportamientoRescatador : public Comportamiento {

  public:
    ComportamientoRescatador(unsigned int size = 0)
        : Comportamiento(size), giro45izq(0), tiene_zapatillas(false), vuelta(false),
          hay_plan(false), recargando(false), continua_recargando(false),
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

    ComportamientoRescatador(std::vector<std::vector<unsigned char>> mapaR,
                             std::vector<std::vector<unsigned char>> mapaC)
        : Comportamiento(mapaR, mapaC), tiene_zapatillas(false), hay_plan(false) {}

    ComportamientoRescatador(const ComportamientoRescatador &comport) : Comportamiento(comport) {}

    ~ComportamientoRescatador() {}

    auto think(Sensores sensores) -> Action;

    auto interact(Action accion, int valor) -> int;

  private:
    /*  ╔═════════════════════════════════════════════════╗
        ║               Variables de Estado               ║
        ╚═════════════════════════════════════════════════╝ */

    int giro45izq;
    bool tiene_zapatillas;
    std::vector<std::vector<unsigned short>> ciclos;
    std::deque<std::tuple<int, int, int>> historial_n1 = {};
    bool vuelta;

    // Nivel 2
    bool hay_plan;
    std::vector<Action> plan;

    // Nivel 4
    bool recargando;
    bool continua_recargando;
    int destRecargaF{0};
    int destRecargaC{0};
    int contadorCall{0};
    std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> puestosX = {};
    bool descubierto_puesto = false;

    /*  ╔═════════════════════════════════════════════════╗
        ║                 Métodos genéricos               ║
        ╚═════════════════════════════════════════════════╝ */

    constexpr inline auto getVisionPosition(int playerF, int playerC, Orientacion orientacion,
                                            int visionIndex) const -> std::pair<int, int>;

    void cartografiar(Sensores &sensores);

    void reiniciarCiclos();

    auto
    decidirAccion(size_t pos, const Sensores &sensores,
                  std::function<bool(unsigned char, const Sensores &, unsigned)> esTransitableFunc)
        -> std::optional<Action>;

    inline auto viablePorAltura(int dif) const -> bool;

    template <int Nivel>
    inline bool esTransitable(unsigned char celda, const Sensores &sensores,
                              unsigned pos) const noexcept;

    auto ComportamientoRescatadorNivel_0(Sensores &sensores) -> Action;
    auto ComportamientoRescatadorNivel_1(Sensores &sensores) -> Action;
    auto ComportamientoRescatadorNivel_2(Sensores &sensores) -> Action;
    auto ComportamientoRescatadorNivel_3(Sensores &sensores) -> Action;
    auto ComportamientoRescatadorNivel_4(Sensores &sensores) -> Action;

    /*  ╔═════════════════════════════════════════════════╗
        ║                 Métodos nivel 0                 ║
        ╚═════════════════════════════════════════════════╝ */

    auto casillasInteresantes(Sensores &sensores) const -> std::vector<size_t>;

    /*  ╔═════════════════════════════════════════════════╗
        ║                 Métodos nivel 1                 ║
        ╚═════════════════════════════════════════════════╝ */

    auto casillasCartografia(Sensores &sensores) const -> std::vector<size_t>;

    /*  ╔═════════════════════════════════════════════════╗
        ║                 Métodos nivel 2                 ║
        ╚═════════════════════════════════════════════════╝ */

    void anularMatriz(std::vector<std::vector<unsigned char>> &matriz);

    auto calcularCoste(Action accion, const EstadoRes &st) -> int;

    void visualizaPlan(const EstadoRes &st, const std::vector<Action> &plan);

    auto rescatadorDijkstra(const EstadoRes &inicio, const EstadoRes &final) -> std::vector<Action>;

    template <int Nivel> auto applyAction(Action accion, const EstadoRes &st) -> EstadoRes;

    template <int Nivel>
    auto casillaAccesibleRescatador(const EstadoRes &st, Action accion) -> bool;

    /*  ╔═════════════════════════════════════════════════╗
        ║                 Métodos nivel 4                 ║
        ╚═════════════════════════════════════════════════╝ */

    auto rescatadorDijkstraDesconocido(
        const EstadoRes &inicio, const EstadoRes &final,
        const std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> &evitar)
        -> std::vector<Action>;

    auto rescatadorDijkstraDesesperado(
        const EstadoRes &inicio, const EstadoRes &final,
        const std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> &evitar)
        -> std::vector<Action>;
};

#endif
