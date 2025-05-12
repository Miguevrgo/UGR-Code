#include "../Comportamientos_Jugador/auxiliar.hpp"
#include "comportamientos/comportamiento.hpp"
#include <algorithm>
#include <array>
#include <boost/functional/hash.hpp>
#include <cstdlib>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

Action ComportamientoAuxiliar::think(Sensores sensores) {
    Action accion{IDLE};

    switch (sensores.nivel) {
    case 0:
        accion = ComportamientoAuxiliarNivel_0(sensores);
        break;
    case 1:
        accion = ComportamientoAuxiliarNivel_1(sensores);
        break;
    case 2:
        accion = IDLE;
        break;
    case 3:
        accion = ComportamientoAuxiliarNivel_3(sensores);
        break;
    case 4:
        accion = ComportamientoAuxiliarNivel_4(sensores);
        break;
    }

    return accion;
}

int ComportamientoAuxiliar::interact(Action accion, int valor) { return 0; }

/*  ╔════════════════════════════════════════════════════════╗
    ║                     Métodos genéricos                  ║
    ╚════════════════════════════════════════════════════════╝ */

constexpr std::pair<int, int> ComportamientoAuxiliar::getVisionPosition(int playerF, int playerC,
                                                                        Orientacion orientacion,
                                                                        int visionIndex) const {
    // clang-format off
    constexpr std::array<std::array<std::pair<int, int>, 16>, 8> desplazamientos = {{
    // Norte
    {{{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}, {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1},
      {-2, 2}, {-3, -3}, {-3, -2}, {-3, -1}, {-3, 0}, {-3, 1}, {-3, 2}, {-3, 3}}},

    // Noreste
    {{{0, 0}, {-1, 0}, {-1, 1}, {0, 1}, {-2, 0}, {-2, 1}, {-2, 2}, {-1, 2},
      {0, 2}, {-3, 0}, {-3, 1}, {-3, 2}, {-3, 3}, {-2, 3}, {-1, 3}, {0, 3}}},

    // Este
    {{{0, 0}, {-1, 1}, {0, 1}, {1, 1}, {-2, 2}, {-1, 2}, {0, 2}, {1, 2},
      {2, 2}, {-3, 3}, {-2, 3}, {-1, 3}, {0, 3}, {1, 3}, {2, 3}, {3, 3}}},

    // Sureste
    {{{0, 0}, {0, 1}, {1, 1}, {1, 0}, {0, 2}, {1, 2}, {2, 2}, {2, 1},
      {2, 0}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {3, 2}, {3, 1}, {3, 0}}},

    // Sur
    {{{0, 0}, {1, 1}, {1, 0}, {1, -1}, {2, 2}, {2, 1}, {2, 0}, {2, -1},
      {2, -2}, {3, 3}, {3, 2}, {3, 1}, {3, 0}, {3, -1}, {3, -2}, {3, -3}}},

    // Suroeste
    {{{0, 0}, {1, 0}, {1, -1}, {0, -1}, {2, 0}, {2, -1}, {2, -2}, {1, -2},
      {0, -2}, {3, 0}, {3, -1}, {3, -2}, {3, -3}, {2, -3}, {1, -3}, {0, -3}}},

    // Oeste
    {{{0, 0}, {1, -1}, {0, -1}, {-1, -1}, {2, -2}, {1, -2}, {0, -2}, {-1, -2},
      {-2, -2}, {3, -3}, {2, -3}, {1, -3}, {0, -3}, {-1, -3}, {-2, -3}, {-3, -3}}},

    // Noroeste
    {{{0, 0}, {0, -1}, {-1, -1}, {-1, 0}, {0, -2}, {-1, -2}, {-2, -2}, {-2, -1},
      {-2, 0}, {0, -3}, {-1, -3}, {-2, -3}, {-3, -3}, {-3, -2}, {-3, -1}, {-3, 0}}}
}}; // clang-format on

    return {playerF + desplazamientos[orientacion][visionIndex].first,
            playerC + desplazamientos[orientacion][visionIndex].second};
}

void ComportamientoAuxiliar::cartografiar(Sensores &sensores) {
    mapaResultado[sensores.posF][sensores.posC] = sensores.superficie[0];
    mapaCotas[sensores.posF][sensores.posC] = sensores.cota[0];

    for (int i = 1; i <= 15; ++i) {
        auto coords = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, i);

        mapaResultado[coords.first][coords.second] = sensores.superficie[i];
        mapaCotas[coords.first][coords.second] = sensores.cota[i];
    }
}

auto ComportamientoAuxiliar::decidirAccion(
    size_t pos, const Sensores &sensores,
    std::function<bool(unsigned char, const Sensores &, unsigned)> transitable)
    -> std::optional<Action> {
    switch (pos) {
    case 1:
        if (viablePorAltura(sensores.cota[1] - sensores.cota[0])) {
            giro45izq = 6;
            return TURN_SR;
        }
        return std::nullopt;
    case 4:
        if (transitable(sensores.superficie[1], sensores, 1) &&
            (viablePorAltura(sensores.cota[1] - sensores.cota[0]))) {
            giro45izq = 6;
            return TURN_SR;
        }
        return std::nullopt;
    case 2:
        if (viablePorAltura(sensores.cota[2] - sensores.cota[0])) {
            return WALK;
        }
        return std::nullopt;
    case 6:
        if (transitable(sensores.superficie[2], sensores, 2) &&
            viablePorAltura(sensores.cota[2] - sensores.cota[0])) {
            return WALK;
        }
        return std::nullopt;
    case 3:
        if (viablePorAltura(sensores.cota[3] - sensores.cota[0])) {
            return TURN_SR;
        }
        return std::nullopt;
    case 8:
        if (transitable(sensores.superficie[3], sensores, 3) &&
            viablePorAltura(sensores.cota[3] - sensores.cota[0])) {
            return TURN_SR;
        }
        return std::nullopt;
    case 5:
        if (transitable(sensores.superficie[2], sensores, 2) &&
            viablePorAltura(sensores.cota[2] - sensores.cota[0])) {
            return WALK;
        }
        return std::nullopt;
    case 7:
        if (transitable(sensores.superficie[2], sensores, 2) &&
            viablePorAltura(sensores.cota[2] - sensores.cota[0])) {
            return WALK;
        } else if (transitable(sensores.superficie[3], sensores, 3) &&
                   viablePorAltura(sensores.cota[3] - sensores.cota[0])) {
            return TURN_SR;
        }
        return std::nullopt;
    default:
        return std::nullopt;
    }
}

inline auto ComportamientoAuxiliar::viablePorAltura(int dif) const -> bool { return abs(dif) < 2; }

template <int Nivel>
inline bool ComportamientoAuxiliar::esTransitable(unsigned char celda, const Sensores &sensores,
                                                  unsigned pos, bool tiene_zap) const noexcept {
    if constexpr (Nivel == 1) {
        return (celda == 'C' || celda == 'D' || celda == 'X' || celda == 'S') &&
               sensores.agentes[pos] == '_';
    } else if constexpr (Nivel == 4) {
        return celda != 'P' && celda != 'M' && (celda != 'B' || tiene_zap) &&
               sensores.agentes[pos] == '_';
    } else {
        return (celda == 'C' || celda == 'D' || celda == 'X') && sensores.agentes[pos] == '_';
    }
}

auto ComportamientoAuxiliar::ComportamientoAuxiliarNivel_0(Sensores &sensores) noexcept -> Action {
    Action accion{TURN_SR}; // Por defecto giramos

    cartografiar(sensores);

    if (sensores.superficie[0] == 'X') { // Se ha llegado a la casilla base
        accion = IDLE;
    } else if (giro45izq) { // Se tiene que realizar todavía el giro
        auto pos = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, 2);
        if (ciclos[pos.first][pos.second] == 0 &&
            esTransitable<0>(sensores.superficie[2], sensores, 2) &&
            viablePorAltura(sensores.cota[2] - sensores.cota[0])) {
            ciclos[sensores.posF][sensores.posC]++;
            giro45izq = 0;
            return WALK;
        }
        accion = TURN_SR;
        giro45izq--;
    } else {
        const auto pos_inter = casillasInteresantes(sensores);

        for (const auto pos : pos_inter) {

            const auto acc = decidirAccion(
                pos, sensores, [this](unsigned char celda, const Sensores &s, unsigned pos) {
                    return this->esTransitable<0>(celda, s, pos);
                });

            if (acc.has_value()) {
                accion = acc.value();

                if (accion == WALK) {
                    auto pos = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, 2);
                    if (ciclos[pos.first][pos.second] > 2 && giro_prueba) {
                        accion = TURN_SR;
                        giro_prueba = false;
                    } else {
                        giro_prueba = true;
                    }
                    ciclos[sensores.posF][sensores.posC]++;
                }

                break;
            }
        }
    }

    return accion;
}

auto ComportamientoAuxiliar::ComportamientoAuxiliarNivel_1(Sensores &sensores) noexcept -> Action {
    Action accion{TURN_SR}; // Por defecto giramos

    cartografiar(sensores);

    // Quitar esta linea para no usar el bug de que IDLE recargue
    if (sensores.energia < 15) {
        return IDLE;
    }

    if (sensores.superficie[0] == 'D') {
        tiene_zapatillas = true;
    }
    if (giro45izq) { // Se tiene que realizar todavía el giro
        if (giro45izq == 6) {
            decision = 1;
        }
        if (giro45izq == 1 && decision == 1) {
            decision = -1;
            accion = TURN_SR;
        } else if (giro45izq == 1 && decision == -1) {
            accion = WALK;
            giro45izq--;
            decision = 0;
        } else {
            accion = TURN_SR;
            giro45izq--;
        }
    } else {
        const auto pos_inter = casillasCartografia(sensores);

        for (const auto pos : pos_inter) {

            const auto acc = decidirAccion(
                pos, sensores, [this](unsigned char celda, const Sensores &s, unsigned pos) {
                    return this->esTransitable<1>(celda, s, pos);
                });

            if (acc.has_value()) {
                accion = acc.value();

                if (accion == WALK) {
                    ciclos[sensores.posF][sensores.posC]++;
                }

                break;
            }
        }
    }

    // Por defecto
    return accion;
}

auto ComportamientoAuxiliar::ComportamientoAuxiliarNivel_3(Sensores &sensores) noexcept -> Action {
    Action accion{IDLE};
    if (!hay_plan) {
        EstadoAux inicio, fin;
        inicio.fila = sensores.posF;
        inicio.col = sensores.posC;
        inicio.brujula = sensores.rumbo;
        inicio.zapatillas = tiene_zapatillas;
        fin.fila = sensores.destinoF;
        fin.col = sensores.destinoC;
        plan = auxiliarAestrella<3>(inicio, fin);
        visualizaPlan(inicio, plan);
        hay_plan = !plan.empty();
    }

    if (hay_plan && !plan.empty()) {
        accion = plan.front();
        plan.erase(plan.begin());
    }

    if (plan.empty()) {
        hay_plan = false;
    }

    return accion;
}

auto ComportamientoAuxiliar::ComportamientoAuxiliarNivel_4(Sensores &sensores) noexcept -> Action {
    Action accion{IDLE};

    cartografiar(sensores);

    if (sensores.superficie[0] == 'D') {
        tiene_zapatillas = true;
    }
    if (sensores.choque) {
        if (continua_recargando) {
            recargando = true;
            continua_recargando = false;
        } else {
            plan.clear();
            hay_plan = false;
        }
    }

    std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> casillas_evitar;
    for (int i = 1; i <= 2; ++i) {
        if (sensores.agentes[i] != '_') {
            auto [f, c] = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, i);
            casillas_evitar.emplace(f, c);
        }
    }

    EstadoAux inicio, fin;
    inicio.fila = sensores.posF;
    inicio.col = sensores.posC;
    inicio.brujula = sensores.rumbo;
    inicio.zapatillas = tiene_zapatillas;
    fin.fila = recargando ? destRecargaF : sensores.destinoF;
    fin.col = recargando ? destRecargaC : sensores.destinoC;

    if (recargando && sensores.agentes[2] != '_' && sensores.superficie[2] == 'X') {
        return IDLE;
    }
    if (recargando && sensores.superficie[0] == 'X') {
        continua_recargando = true;
        recargando = false;
    }

    if (continua_recargando) {
        if (sensores.energia > 2990 || sensores.vida < 400 ||
            (fin.fila != -1 && fin.col != -1 && sensores.energia > 1100)) {
            continua_recargando = false;
        }
        return IDLE;
    }

    if (!hay_plan) {
        if (fin.fila == -1 && fin.col == -1) { // No hay CALL_ON
            if (((sensores.energia < 1500 && sensores.vida > 400 && !recargando) ||
                 explorarDesconocido(inicio).empty())) {

                std::vector<std::pair<int, int>> puestos;
                for (size_t i = 0; i < mapaResultado.size(); ++i) {
                    for (size_t j = 0; j < mapaResultado[0].size(); ++j) {
                        if (mapaResultado[i][j] == 'X')
                            puestos.emplace_back(i, j);
                    }
                }

                if (!puestos.empty()) {
                    recargando = true;

                    auto mejor = std::min_element(
                        puestos.begin(), puestos.end(), [&](const auto &a, const auto &b) {
                            int coste_a = 0, coste_b = 0;
                            auto plan_a = auxiliarAestrella<4>(inicio, {a.first, a.second});
                            auto plan_b = auxiliarAestrella<4>(inicio, {b.first, b.second});
                            EstadoAux sim_a = inicio, sim_b = inicio;

                            for (auto acc : plan_a)
                                coste_a += calcularCoste<4>(acc, sim_a),
                                    sim_a = applyAction(acc, sim_a);
                            for (auto acc : plan_b)
                                coste_b += calcularCoste<4>(acc, sim_b),
                                    sim_b = applyAction(acc, sim_b);

                            return (!plan_a.empty() && (plan_b.empty() || coste_a < coste_b));
                        });

                    destRecargaF = mejor->first;
                    destRecargaC = mejor->second;
                }
            } else {
                return explorarDesconocido(inicio)[0];
            }
        } else {
            plan = auxiliarAestrella<4>(inicio, fin);
            visualizaPlan(inicio, plan);
            if (plan.empty()) {
                plan = auxiliarADesconocido(inicio, fin, casillas_evitar);
                visualizaPlan(inicio, plan);
            }
            hay_plan = !plan.empty();
            if (!hay_plan) {
                return IDLE;
            }
        }
    }

    if (hay_plan && !plan.empty()) {
        accion = plan.front();
        plan.erase(plan.begin());

        EstadoAux simulado = applyAction(accion, inicio);
        if (((simulado.fila == inicio.fila && simulado.col == inicio.col) ||
             sensores.agentes[2] != '_') &&
            accion == WALK) {
            plan.clear();
            plan = auxiliarADesconocido(inicio, fin, casillas_evitar);
            hay_plan = !plan.empty();
            if (hay_plan) {
                accion = plan.front();
                plan.erase(plan.begin());
            } else {
                accion = IDLE;
            }
        }

        for (int i = 0; i <= 15; ++i) {
            if (getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, i).first ==
                    fin.fila &&
                getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, i).second ==
                    fin.col &&
                !recargando) {
                plan.clear();
                accion = IDLE;
            }
        }
    }

    hay_plan = !plan.empty();

    return accion;
}
/*  ╔════════════════════════════════════════════════════════╗
    ║                     Métodos nivel 0                    ║
    ╚════════════════════════════════════════════════════════╝ */

std::vector<size_t>
ComportamientoAuxiliar::casillasInteresantes(Sensores &sensores) const noexcept {
    std::vector<size_t> interesantes;

    // Movimientos de un tiempo
    if (sensores.superficie[2] == 'X') {
        interesantes.emplace_back(2);
    }
    if (sensores.superficie[6] == 'X') {
        interesantes.emplace_back(6);
    }

    // Llegada
    for (size_t i = 1; i < 9; ++i) {
        if (sensores.superficie[i] == 'X' && i != 2 && i != 6) {
            interesantes.emplace_back(i);
        }
    }

    // Camino
    if (sensores.superficie[2] == 'C') {
        interesantes.emplace_back(2);
    }
    if (sensores.superficie[3] == 'C') {
        interesantes.emplace_back(3);
    }
    for (size_t i = 1; i < 9; ++i) {
        if (sensores.superficie[i] == 'C' && i != 2 && i != 3) {
            interesantes.emplace_back(i);
        }
    }

    interesantes.erase(std::remove_if(interesantes.begin(), interesantes.end(),
                                      [&](size_t i) {
                                          int pos = i;
                                          return !esTransitable<0>(sensores.superficie[pos],
                                                                   sensores, pos);
                                      }),
                       interesantes.end());

    std::stable_sort(interesantes.begin(), interesantes.end(), [&](size_t a, size_t b) {
        auto prioridad = [](unsigned char celda) -> int {
            if (celda == 'X')
                return 0;
            if (celda == 'C')
                return 1;
            return 2;
        };

        int prio_a = prioridad(sensores.superficie[a]);
        int prio_b = prioridad(sensores.superficie[b]);

        if (prio_a != prio_b) {
            return prio_a < prio_b;
        }

        auto pos_a = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, a);
        auto pos_b = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, b);

        return ciclos[pos_a.first][pos_a.second] < ciclos[pos_b.first][pos_b.second];
    });

    return interesantes;
}

/*  ╔════════════════════════════════════════════════════════╗
    ║                     Métodos nivel 1                    ║
    ╚════════════════════════════════════════════════════════╝ */

std::vector<size_t> ComportamientoAuxiliar::casillasCartografia(Sensores &sensores) const {
    std::vector<size_t> interesantes;

    std::array<int, 10> posiciones = {2, 3, 6, 8, 7, 1, 5, 7, 4};

    for (auto pos : posiciones) {
        if (sensores.superficie[pos] == 'C' || sensores.superficie[pos] == 'S' ||
            sensores.superficie[pos] == 'D' || sensores.superficie[pos] == 'X') {
            interesantes.emplace_back(pos);
        }
    }

    // Prioridad: D > C > S
    const auto prioridad = [](unsigned char celda) -> int {
        if (celda == 'D')
            return 1;
        if (celda == 'C' || celda == 'S')
            return 2;
        if (celda == 'X')
            return 3;
        return 4;
    };

    interesantes.erase(
        std::remove_if(interesantes.begin(), interesantes.end(),
                       [&](size_t i) {
                           int pos = i;
                           return !viablePorAltura(sensores.cota[i] - sensores.cota[0]) ||
                                  !esTransitable<1>(sensores.superficie[i], sensores, pos);
                       }),
        interesantes.end());

    std::sort(interesantes.begin(), interesantes.end(), [&](size_t a, size_t b) {
        int prio_a = prioridad(sensores.superficie[a]);
        int prio_b = prioridad(sensores.superficie[b]);

        auto pos_a = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, a);
        auto pos_b = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, b);

        if (prio_a != prio_b) {
            if (ciclos[pos_a.first][pos_a.second] - ciclos[pos_b.first][pos_b.second] < 3) {
                return true;
            }
            return prio_a < prio_b;
        } else {
            return ciclos[pos_a.first][pos_a.second] < ciclos[pos_b.first][pos_b.second];
        }
    });

    return interesantes;
}

/*  ╔════════════════════════════════════════════════════════╗
    ║                     Métodos nivel 3                    ║
    ╚════════════════════════════════════════════════════════╝ */

constexpr std::array<std::pair<int, int>, 8> offset_orientacion{
    {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}};

inline int heuristica(const EstadoAux &a, const EstadoAux &b) {
    return std::max(std::abs(a.fila - b.fila), std::abs(a.col - b.col));
}

void ComportamientoAuxiliar::anularMatriz(
    std::vector<std::vector<unsigned char>> &matriz) noexcept {
    for (auto &fila : matriz) {
        std::fill(fila.begin(), fila.end(), 0);
    }
}

template <int Nivel>
int ComportamientoAuxiliar::calcularCoste(Action action, const EstadoAux &st) const noexcept {
    const char casilla_inicial = mapaResultado[st.fila][st.col];
    int coste = 1;

    const auto [df, dc] = offset_orientacion[st.brujula];
    int fila_final = st.fila + df;
    int col_final = st.col + dc;

    int altura = mapaCotas[fila_final][col_final] - mapaCotas[st.fila][st.col];

    switch (action) {
    case WALK:
        switch (casilla_inicial) {
        case '?':
            coste = 15;
            break;
        case 'A':
            if constexpr (Nivel == 3)
                coste = 100 + 10 * altura;
            else
                coste = 135 + 10 * altura;
            break;
        case 'T':
            coste = 20 + 5 * altura;
            break;
        case 'S':
            coste = 2 + altura;
            break;
        default:
            coste = 1;
            break;
        }
        break;
    case TURN_SR:
        switch (casilla_inicial) {
        case '?':
            coste = 2;
            break;
        case 'A':
            if constexpr (Nivel == 3)
                coste = 16;
            else
                coste = 33;
            break;
        case 'T':
            coste = 3;
            break;
        case 'S':
            coste = 1;
            break;
        default:
            coste = 1;
            break;
        }
        break;
    default:
        coste = 1;
        break;
    }

    return coste;
}

void ComportamientoAuxiliar::visualizaPlan(const EstadoAux &st,
                                           const std::vector<Action> &plan) noexcept {
    anularMatriz(mapaConPlan);
    EstadoAux cst = st;

    for (const auto &accion : plan) {

        switch (accion) {
        case WALK:
            cst.fila += offset_orientacion[cst.brujula].first;
            cst.col += offset_orientacion[cst.brujula].second;
            mapaConPlan[cst.fila][cst.col] = 2;
            break;
        case TURN_SR:
            cst.brujula = (cst.brujula + 1) % 8;
            break;
        default:
            std::exit(1);
            break;
        }
    }
}

struct ComparadorAEstrella {
    const EstadoAux objetivo;

    ComparadorAEstrella(EstadoAux fin) : objetivo(std::move(fin)) {}

    bool operator()(const NodoAux &a, const NodoAux &b) const {
        return a.coste + heuristica(a.estado, objetivo) > b.coste + heuristica(b.estado, objetivo);
    }
};

template <int Nivel>
auto ComportamientoAuxiliar::auxiliarAestrella(const EstadoAux &inicio,
                                               const EstadoAux &final) noexcept
    -> std::vector<Action> {

    std::priority_queue<NodoAux, std::vector<NodoAux>, ComparadorAEstrella> frontier{
        ComparadorAEstrella(final)};

    std::unordered_map<EstadoAux, int> coste_minimo;

    frontier.emplace(inicio, std::vector<Action>{}, 0);
    coste_minimo[inicio] = 0;

    while (!frontier.empty()) {
        const NodoAux actual = frontier.top();
        frontier.pop();

        EstadoAux estado_actual = actual.estado;

        if (estado_actual.fila == final.fila && estado_actual.col == final.col) {
            return actual.secuencia;
        }

        if (mapaResultado[estado_actual.fila][estado_actual.col] == 'D') {
            estado_actual.zapatillas = true;
        }

        for (Action accion : {WALK, TURN_SR}) {
            EstadoAux nuevo = applyAction(accion, estado_actual);

            if (nuevo.fila == estado_actual.fila && nuevo.col == estado_actual.col &&
                accion == WALK)
                continue;

            const int nuevo_coste = actual.coste + calcularCoste<Nivel>(accion, estado_actual);

            if (!coste_minimo.count(nuevo) || nuevo_coste < coste_minimo[nuevo]) {
                coste_minimo[nuevo] = nuevo_coste;
                auto nueva_seq{actual.secuencia};
                nueva_seq.emplace_back(accion);
                frontier.emplace(nuevo, std::move(nueva_seq), nuevo_coste);
            }
        }
    }

    return {};
}

auto ComportamientoAuxiliar::applyAction(Action accion, const EstadoAux &st) noexcept -> EstadoAux {
    EstadoAux next = st;
    switch (accion) {
    case TURN_SR:
        next.brujula = (st.brujula + 1) % 8;
        break;
    case WALK:
        if (casillaAccesibleAuxiliar(st, accion)) {
            next.fila += offset_orientacion[st.brujula].first;
            next.col += offset_orientacion[st.brujula].second;
        }
        break;
    default:
        break;
    }

    return next;
}

auto ComportamientoAuxiliar::casillaAccesibleAuxiliar(const EstadoAux &st, Action accion) noexcept
    -> bool {
    auto esTransitableN3 = [&](std::size_t f2, std::size_t c2, bool zap) -> bool {
        const char terreno = mapaResultado[f2][c2];

        return terreno != 'P' && terreno != 'M' && (terreno != 'B' || (terreno == 'B' && zap));
    };

    const std::size_t f = st.fila + offset_orientacion[st.brujula].first;
    const std::size_t c = st.col + offset_orientacion[st.brujula].second;

    return (esTransitableN3(f, c, st.zapatillas) &&
            viablePorAltura(mapaCotas[st.fila][st.col] - mapaCotas[f][c])) ||
           mapaResultado[f][c] == '?';
}

/*  ╔════════════════════════════════════════════════════════╗
    ║                     Métodos nivel 4                    ║
    ╚════════════════════════════════════════════════════════╝ */

auto ComportamientoAuxiliar::auxiliarADesconocido(
    const EstadoAux &inicio, const EstadoAux &final,
    const std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> &evitar)
    -> std::vector<Action> {

    std::priority_queue<NodoAux, std::vector<NodoAux>, ComparadorAEstrella> frontier{
        ComparadorAEstrella(final)};
    std::unordered_map<EstadoAux, int> coste_minimo;

    frontier.emplace(inicio, std::vector<Action>{}, 0);
    coste_minimo[inicio] = 0;

    while (!frontier.empty()) {
        const NodoAux actual = frontier.top();
        frontier.pop();

        EstadoAux estado_actual = actual.estado;

        // Comprobar si está en vista
        for (int i = 1; i <= 15; ++i) {
            if (getVisionPosition(estado_actual.fila, estado_actual.col,
                                  Orientacion(estado_actual.brujula),
                                  i) == std::make_pair(final.fila, final.col)) {
                return actual.secuencia;
            }
        }

        if (mapaResultado[estado_actual.fila][estado_actual.col] == 'D') {
            estado_actual.zapatillas = true;
        }

        for (Action accion : {WALK, TURN_SR}) {
            EstadoAux nuevo = applyAction(accion, estado_actual);

            if (accion == WALK &&
                    (nuevo.fila == estado_actual.fila && nuevo.col == estado_actual.col) ||
                (evitar.count({nuevo.fila, nuevo.col}) > 0))
                continue;

            const int nuevo_coste = actual.coste + calcularCoste<4>(accion, estado_actual);

            if (!coste_minimo.count(nuevo) || nuevo_coste < coste_minimo[nuevo]) {
                coste_minimo[nuevo] = nuevo_coste;
                auto nueva_seq{actual.secuencia};
                nueva_seq.emplace_back(accion);
                frontier.emplace(nuevo, std::move(nueva_seq), nuevo_coste);
            }
        }
    }

    return {};
}

auto ComportamientoAuxiliar::explorarDesconocido(const EstadoAux &inicio) -> std::vector<Action> {
    constexpr int MAX_RADIO = 8;
    constexpr int MAX_CANDIDATOS = 5;
    std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> visitadas;

    for (int radio = 1; radio < MAX_RADIO; ++radio) {
        std::vector<std::tuple<int, int, int, std::vector<Action>>> candidatos; // f, c, coste, plan

        for (int df = -radio; df <= radio; ++df) {
            for (int dc = -radio; dc <= radio; ++dc) {
                if (abs(df) != radio && abs(dc) != radio)
                    continue; // Solo borde

                int f = inicio.fila + df;
                int c = inicio.col + dc;

                if (f < 0 || f >= mapaResultado.size() || c < 0 || c >= mapaResultado[0].size())
                    continue;

                if (!visitadas.insert({f, c}).second)
                    continue;

                if (mapaResultado[f][c] == '?') {
                    EstadoAux destino = inicio;
                    destino.fila = f;
                    destino.col = c;

                    auto plan = auxiliarAestrella<4>(inicio, destino);
                    if (!plan.empty()) {
                        int coste = 0;
                        EstadoAux tmp = inicio;
                        for (const auto &accion : plan) {
                            coste += calcularCoste<4>(accion, tmp);
                            tmp = applyAction(accion, tmp);
                        }
                        candidatos.emplace_back(f, c, coste, std::move(plan));

                        if (candidatos.size() == MAX_CANDIDATOS)
                            break;
                    }
                }
            }
            if (candidatos.size() == MAX_CANDIDATOS)
                break;
        }

        if (!candidatos.empty()) {
            auto mejor = std::min_element(candidatos.begin(), candidatos.end(),
                                          [](const auto &a, const auto &b) {
                                              return std::get<2>(a) < std::get<2>(b); // menor coste
                                          });
            return std::get<3>(*mejor); // plan
        }
    }

    return {}; // No se encontró ningún camino a casillas desconocidas
}
