#include "../Comportamientos_Jugador/rescatador.hpp"
#include "comportamientos/comportamiento.hpp"
#include <algorithm>
#include <array>
#include <boost/functional/hash.hpp>
#include <cstddef>
#include <queue>
#include <unordered_map>
#include <unordered_set>

Action ComportamientoRescatador::think(Sensores sensores) {
    Action accion{IDLE};

    switch (sensores.nivel) {
    case 0:
        accion = ComportamientoRescatadorNivel_0(sensores);
        break;
    case 1:
        accion = ComportamientoRescatadorNivel_1(sensores);
        break;
    case 2:
        accion = ComportamientoRescatadorNivel_2(sensores);
        break;
    case 3:
        accion = IDLE;
        break;
    case 4:
        accion = ComportamientoRescatadorNivel_4(sensores);
        break;
    }

    return accion;
}

int ComportamientoRescatador::interact(Action accion, int valor) { return 0; }

/*  ╔════════════════════════════════════════════════════════╗
    ║                     Métodos genéricos                  ║
    ╚════════════════════════════════════════════════════════╝ */

constexpr std::pair<int, int> ComportamientoRescatador::getVisionPosition(int playerF, int playerC,
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

void ComportamientoRescatador::cartografiar(Sensores &sensores) {
    mapaResultado[sensores.posF][sensores.posC] = sensores.superficie[0];
    mapaCotas[sensores.posF][sensores.posC] = sensores.cota[0];

    for (int i = 1; i <= 15; ++i) {
        auto coords = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, i);
        mapaResultado[coords.first][coords.second] = sensores.superficie[i];
        mapaCotas[coords.first][coords.second] = sensores.cota[i];

        if (sensores.superficie[i] == 'X') {
            auto [_, insertado] = puestosX.emplace(coords);
            if (insertado) {
                descubierto_puesto = true;
            }
        }
    }
}

void ComportamientoRescatador::reiniciarCiclos() {
    ciclos = std::vector<std::vector<unsigned short>>(
        ciclos.size(), std::vector<unsigned short>(ciclos.size(), 0));
}

auto ComportamientoRescatador::decidirAccion(
    size_t pos, const Sensores &sensores,
    std::function<bool(unsigned char, const Sensores &, unsigned)> transitable)
    -> std::optional<Action> {
    switch (pos) {
    case 1:
        if (viablePorAltura(sensores.cota[1] - sensores.cota[0])) {
            giro45izq = 1;
            return TURN_L;
        }
        return std::nullopt;
    case 4:
        if (transitable(sensores.superficie[1], sensores, 1) &&
            (viablePorAltura(sensores.cota[1] - sensores.cota[0]) ||
             viablePorAltura(sensores.cota[4] - sensores.cota[0]))) {
            giro45izq = 1;
            return TURN_L;
        } else if (transitable(sensores.superficie[2], sensores, 2) &&
                   viablePorAltura(sensores.cota[2] - sensores.cota[0])) {
            giro45izq = 1;
            return WALK;
        }
        return std::nullopt;
    case 9:
    case 10:
        if (transitable(sensores.superficie[1], sensores, 1) &&
            transitable(sensores.superficie[4], sensores, 4) &&
            (viablePorAltura(sensores.cota[1] - sensores.cota[0]) ||
             viablePorAltura(sensores.cota[4] - sensores.cota[0]))) {
            giro45izq = 1;
            return TURN_L;
        }
        return std::nullopt;
    case 2:
        if (viablePorAltura(sensores.cota[2] - sensores.cota[0])) {
            return WALK;
        }
        return std::nullopt;
    case 6:
        if (transitable(sensores.superficie[2], sensores, 2) &&
            viablePorAltura(sensores.cota[6] - sensores.cota[0])) {
            return RUN;
        }
        return std::nullopt;
    case 11:
    case 12:
    case 13:
        if (transitable(sensores.superficie[2], sensores, 2) &&
            transitable(sensores.superficie[6], sensores, 6) &&
            viablePorAltura(sensores.cota[6] - sensores.cota[0])) {
            return RUN;
        }
        return std::nullopt;
    case 3:
        if (viablePorAltura(sensores.cota[3] - sensores.cota[0])) {
            return TURN_SR;
        }
        return std::nullopt;
    case 8:
        if (transitable(sensores.superficie[3], sensores, 3) &&
            (viablePorAltura(sensores.cota[3] - sensores.cota[0]) ||
             viablePorAltura(sensores.cota[8] - sensores.cota[0]))) {
            return TURN_SR;
        }
        return std::nullopt;
    case 14:
    case 15:
        if (transitable(sensores.superficie[3], sensores, 3) &&
            transitable(sensores.superficie[8], sensores, 8)) {
            return TURN_SR;
        }
        return std::nullopt;
    case 5:
        if (transitable(sensores.superficie[2], sensores, 2) &&
            viablePorAltura(sensores.cota[2] - sensores.cota[0])) {
            return WALK;
        } else if (transitable(sensores.superficie[1], sensores, 1) &&
                   viablePorAltura(sensores.cota[1] - sensores.cota[0])) {
            giro45izq = 1;
            return TURN_L;
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

inline auto ComportamientoRescatador::viablePorAltura(int dif) const -> bool {
    return abs(dif) < 2 || (tiene_zapatillas && abs(dif) < 3);
}

template <int Nivel>
inline bool ComportamientoRescatador::esTransitable(unsigned char celda, const Sensores &sensores,
                                                    unsigned pos) const noexcept {
    if constexpr (Nivel == 1) {
        return (celda == 'C' || celda == 'D' || celda == 'X' || celda == 'S') &&
               sensores.agentes[pos] == '_';
    } else {
        return (celda == 'C' || celda == 'D' || celda == 'X') &&
               (sensores.agentes[pos] == '_' || sensores.agentes[pos] == 0);
    }
}

auto ComportamientoRescatador::ComportamientoRescatadorNivel_0(Sensores &sensores) -> Action {
    Action accion{TURN_L}; // Por defecto giramos

    cartografiar(sensores);

    // Obtiene zapatillas
    if (sensores.superficie[0] == 'D') {
        tiene_zapatillas = true;
        reiniciarCiclos();
    }

    if (sensores.superficie[0] == 'X') { // Se ha llegado a la casilla base
        accion = IDLE;
    } else if (giro45izq) { // Se tiene que realizar todavía el giro
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

                if (accion == WALK || accion == RUN) {
                    ciclos[sensores.posF][sensores.posC]++;
                }

                return accion;
            }
        }
    }

    return accion;
}

auto ComportamientoRescatador::ComportamientoRescatadorNivel_1(Sensores &sensores) -> Action {
    Action accion{TURN_L}; // Por defecto giramos

    cartografiar(sensores);

    // Obtiene zapatillas
    if (sensores.superficie[0] == 'D') {
        tiene_zapatillas = true;
        reiniciarCiclos();
    }

    // Quitar esta linea para no usar el bug de que IDLE recargue
    if (sensores.energia < 15) {
        return IDLE;
    }

    if (historial_n1.size() >= 25)
        historial_n1.pop_front();

    historial_n1.emplace_back(sensores.posF, sensores.posC, sensores.rumbo);

    int repeticiones = std::count(historial_n1.begin(), historial_n1.end(),
                                  std::make_tuple(sensores.posF, sensores.posC, sensores.rumbo));

    if (repeticiones >= 3) {
        for (size_t pos : {2, 3, 1}) {
            auto acc = decidirAccion(pos, sensores,
                                     [this](unsigned char celda, const Sensores &s, unsigned pos) {
                                         return this->esTransitable<1>(celda, s, pos);
                                     });

            if (acc.has_value()) {
                return acc.value();
            }
        }

        return TURN_L;
    }

    if (vuelta) {
        vuelta = false;
        accion = TURN_L;
        return accion;
    }
    if (giro45izq) { // Se tiene que realizar todavía el giro
        accion = TURN_SR;
        giro45izq--;
    } else {

        auto orient_izq = static_cast<Orientacion>((sensores.rumbo + 6) % 8); // rumbo - 2
        auto orient_der = static_cast<Orientacion>((sensores.rumbo + 2) % 8); // rumbo + 2
        auto orient_atras = static_cast<Orientacion>((sensores.rumbo + 4) % 8);

        auto pos_izq = getVisionPosition(sensores.posF, sensores.posC, orient_izq, 1);
        auto pos_der = getVisionPosition(sensores.posF, sensores.posC, orient_der, 1);
        auto pos_atras = getVisionPosition(sensores.posF, sensores.posC, orient_atras, 1);

        auto sin_cartografiar = [&](std::pair<int, int> pos) {
            return pos.first >= 0 && pos.first < static_cast<int>(mapaResultado.size()) &&
                   pos.second >= 0 && pos.second < static_cast<int>(mapaResultado[0].size()) &&
                   mapaResultado[pos.first][pos.second] == '?';
        };

        if (sin_cartografiar(pos_izq)) {
            return TURN_L;
        } else if (sin_cartografiar(pos_der)) {
            return TURN_SR;
        } else if (sin_cartografiar(pos_atras)) {
            vuelta = true;
            return TURN_L;
        }

        const auto pos_inter = casillasCartografia(sensores);
        for (const auto pos : pos_inter) {

            const auto acc = decidirAccion(
                pos, sensores, [this](unsigned char celda, const Sensores &s, unsigned pos) {
                    return this->esTransitable<1>(celda, s, pos);
                });

            if (acc.has_value()) {
                accion = acc.value();

                if (accion == WALK || accion == RUN) {
                    ciclos[sensores.posF][sensores.posC]++;
                }

                return accion;
            }
        }
    }

    // Por defecto
    return accion;
}

auto ComportamientoRescatador::ComportamientoRescatadorNivel_2(Sensores &sensores) -> Action {
    Action accion{IDLE};
    if (!hay_plan) {
        EstadoRes inicio, fin;
        inicio.fila = sensores.posF;
        inicio.col = sensores.posC;
        inicio.brujula = sensores.rumbo;
        inicio.zapatillas = tiene_zapatillas;
        fin.fila = sensores.destinoF;
        fin.col = sensores.destinoC;
        plan = rescatadorDijkstra(inicio, fin);
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

auto ComportamientoRescatador::ComportamientoRescatadorNivel_4(Sensores &sensores) -> Action {
    Action accion{IDLE};

    // Cartografiar en cada turno
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

    if (sensores.gravedad) {
        if (contadorCall == 0) {
            accion = CALL_ON;
            contadorCall++;
            return accion;
        } else if (contadorCall > mapaResultado.size() * 2.5) {
            accion = CALL_OFF;
            contadorCall = 0;
            return accion;
        } else {
            contadorCall++;
        }
    }

    std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> casillas_evitar;
    for (int i = 1; i <= 6; ++i) {
        if (sensores.agentes[i] != '_') {
            auto [f, c] = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, i);
            casillas_evitar.emplace(f, c);
        }
    }

    EstadoRes inicio, fin;
    inicio.fila = sensores.posF;
    inicio.col = sensores.posC;
    inicio.brujula = sensores.rumbo;
    inicio.zapatillas = tiene_zapatillas;
    fin.fila = recargando ? destRecargaF : sensores.destinoF;
    fin.col = recargando ? destRecargaC : sensores.destinoC;

    if ((inicio.fila != fin.fila) || (inicio.col != fin.col)) {
        contadorCall = 0;
    }

    if (recargando && sensores.superficie[0] == 'X') {
        continua_recargando = true;
        recargando = false;
    }

    if (continua_recargando) {
        continua_recargando =
            ((sensores.energia < 2990 && sensores.vida > 700) ||
             (sensores.energia < 1500 && sensores.vida > 300) && sensores.superficie[0] == 'X');
        return IDLE;
    }

    if ((sensores.energia < 660 && sensores.vida > 500 && !recargando) || descubierto_puesto) {
        if (recargando && descubierto_puesto) {
            plan.clear();
            hay_plan = false;
        }

        std::vector<std::pair<int, int>> puestos(puestosX.begin(), puestosX.end());

        if (!puestos.empty()) {
            auto mejor =
                std::min_element(puestos.begin(), puestos.end(), [&](const auto &a, const auto &b) {
                    auto plan_a = rescatadorDijkstra(inicio, {a.first, a.second});
                    auto plan_b = rescatadorDijkstra(inicio, {b.first, b.second});
                    int coste_a = plan_a.size() * 10;
                    int coste_b = plan_b.size() * 10;

                    EstadoRes sim_a = inicio, sim_b = inicio;
                    for (auto acc : plan_a)
                        coste_a += calcularCoste(acc, sim_a), sim_a = applyAction<2>(acc, sim_a);
                    for (auto acc : plan_b)
                        coste_b += calcularCoste(acc, sim_b), sim_b = applyAction<2>(acc, sim_b);

                    return (!plan_a.empty() && (plan_b.empty() || coste_a < coste_b));
                });

            int coste = 0;
            auto plan = rescatadorDijkstra(inicio, {mejor->first, mejor->second});
            EstadoRes sim = inicio;
            for (auto acc : plan)
                coste += calcularCoste(acc, sim), sim = applyAction<2>(acc, sim);

            if (coste < sensores.energia) {
                destRecargaF = mejor->first;
                destRecargaC = mejor->second;
                recargando = true;
                descubierto_puesto = false;
            }
        }
    }

    if (!hay_plan && contadorCall == 0) {
        plan = rescatadorDijkstraDesconocido(inicio, fin, casillas_evitar);
        if (plan.empty() && sensores.energia > 2500) {
            plan = rescatadorDijkstraDesesperado(inicio, fin, casillas_evitar);
        }
        if (plan.empty()) {
            return ComportamientoRescatadorNivel_1(sensores);
        }
        visualizaPlan(inicio, plan);
        hay_plan = !plan.empty();
    }

    if (hay_plan && !plan.empty()) {
        accion = plan.front();
        plan.erase(plan.begin());

        EstadoRes simulado = applyAction<2>(accion, inicio);

        bool no_avanza = simulado.fila == inicio.fila && simulado.col == inicio.col;
        if ((accion == WALK && (no_avanza || sensores.agentes[2] != '_')) ||
            (accion == RUN &&
             (no_avanza || sensores.agentes[2] != '_' || sensores.agentes[6] != '_'))) {

            plan.clear();
            plan = rescatadorDijkstraDesconocido(inicio, fin, casillas_evitar);
            hay_plan = !plan.empty();
            if (hay_plan) {
                visualizaPlan(inicio, plan);
                accion = plan.front();
                plan.erase(plan.begin());
            } else {
                accion = IDLE;
            }
        }

        hay_plan = !plan.empty();
    }

    return accion;
}

/*  ╔════════════════════════════════════════════════════════╗
    ║                     Métodos nivel 0                    ║
    ╚════════════════════════════════════════════════════════╝ */

std::vector<size_t> ComportamientoRescatador::casillasInteresantes(Sensores &sensores) const {
    std::vector<size_t> interesantes;

    // Movimientos de un tiempo
    if (sensores.superficie[2] == 'X') {
        interesantes.emplace_back(2);
    }
    if (sensores.superficie[6] == 'X') {
        interesantes.emplace_back(6);
    }

    // Llegada
    for (size_t i = 1; i < 16; ++i) {
        if (sensores.superficie[i] == 'X' && i != 2 && i != 6) {
            interesantes.emplace_back(i);
        }
    }

    // Zapatillas
    if (!tiene_zapatillas) {
        for (size_t i = 1; i < 16; ++i) {
            if (sensores.superficie[i] == 'D') {
                interesantes.emplace_back(i);
            }
        }
    }

    // Movimientos de un tiempo
    if (sensores.superficie[6] == 'C') {
        interesantes.emplace_back(6);
    }
    if (sensores.superficie[2] == 'C') {
        interesantes.emplace_back(2);
    }
    // Camino
    for (size_t i = 1; i < 16; ++i) {
        if (sensores.superficie[i] == 'C' && i != 2 && i != 6) {
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
        auto tipo_a = sensores.superficie[a];
        auto tipo_b = sensores.superficie[b];

        auto prioridad = [](unsigned char celda) -> int {
            if (celda == 'X')
                return 0;
            if (celda == 'D')
                return 1;
            if (celda == 'C')
                return 2;
            return 3;
        };

        int prio_a = prioridad(tipo_a);
        int prio_b = prioridad(tipo_b);

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

std::vector<size_t> ComportamientoRescatador::casillasCartografia(Sensores &sensores) const {
    std::vector<size_t> interesantes;

    std::array<int, 9> posiciones = {6, 2, 3, 8, 4, 12, 5, 7, 11};

    for (auto pos : posiciones) {
        if (sensores.superficie[pos] == 'C' || sensores.superficie[pos] == 'S' ||
            (!tiene_zapatillas && sensores.superficie[pos] == 'D') ||
            sensores.superficie[pos] == 'X') {
            interesantes.emplace_back(pos);
        }
    }

    // Prioridad: X > D > C
    const auto prioridad = [](unsigned char celda) -> int {
        if (celda == 'D')
            return 1;
        if (celda == 'C' || celda == 'S')
            return 2;
        return 4;
    };

    interesantes.erase(
        std::remove_if(interesantes.begin(), interesantes.end(),
                       [&](size_t i) {
                           int pos = i;
                           if (i == 5 || i == 7) {
                               i = 6;
                           }
                           return !viablePorAltura(sensores.cota[i] - sensores.cota[0]) ||
                                  !esTransitable<1>(sensores.superficie[i], sensores, pos);
                       }),
        interesantes.end());

    std::sort(interesantes.begin(), interesantes.end(), [&](size_t a, size_t b) {
        int prio_a = prioridad(sensores.superficie[a]);
        int prio_b = prioridad(sensores.superficie[b]);

        if (prio_a != prio_b) {
            return prio_a < prio_b;
        } else {
            auto pos_a = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, a);
            auto pos_b = getVisionPosition(sensores.posF, sensores.posC, sensores.rumbo, b);
            return ciclos[pos_a.first][pos_a.second] < ciclos[pos_b.first][pos_b.second];
        }
    });

    return interesantes;
}

/*  ╔════════════════════════════════════════════════════════╗
    ║                     Métodos nivel 2                    ║
    ╚════════════════════════════════════════════════════════╝ */

constexpr std::array<std::pair<int, int>, 8> offset_orientacion{
    {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}};

void ComportamientoRescatador::anularMatriz(std::vector<std::vector<unsigned char>> &matriz) {
    for (auto &fila : matriz) {
        std::fill(fila.begin(), fila.end(), 0);
    }
}

auto ComportamientoRescatador::calcularCoste(Action action, const EstadoRes &st) -> int {
    const char casilla_inicial = mapaResultado[st.fila][st.col];
    int fila_final = st.fila;
    int col_final = st.col;
    int coste = 0;

    const auto [df, dc] = offset_orientacion[st.brujula];

    switch (action) {
    case WALK:
        fila_final += df;
        col_final += dc;
        {
            int signo = 0;
            int alt_inicial = mapaCotas[st.fila][st.col];
            int alt_final = mapaCotas[fila_final][col_final];
            int dif = alt_final - alt_inicial;
            signo = (dif > 0) ? 1 : (dif < 0) ? -1 : 0;

            switch (casilla_inicial) {
            case '?':
                coste = 60;
                break;
            case 'A':
                coste = 100 + 10 * signo;
                break;
            case 'T':
                coste = 20 + 5 * signo;
                break;
            case 'S':
                coste = 2 + 1 * signo;
                break;
            default:
                coste = 1;
                break;
            }
        }
        break;

    case RUN:
        fila_final += 2 * df;
        col_final += 2 * dc;
        {
            int signo = 0;
            int alt_inicial = mapaCotas[st.fila][st.col];
            int alt_final = mapaCotas[fila_final][col_final];
            int dif = alt_final - alt_inicial;
            signo = (dif > 0) ? 1 : (dif < 0) ? -1 : 0;

            switch (casilla_inicial) {
            case '?':
                coste = 60;
                break;
            case 'A':
                coste = 150 + 15 * signo;
                break;
            case 'T':
                coste = 35 + 5 * signo;
                break;
            case 'S':
                coste = 3 + 2 * signo;
                break;
            default:
                coste = 1;
                break;
            }
        }
        break;

    case TURN_L:
        switch (casilla_inicial) {
        case '?':
            coste = 15;
            break;
        case 'A':
            coste = 30;
            break;
        case 'T':
            coste = 5;
            break;
        case 'S':
            coste = 1;
            break;
        default:
            coste = 1;
            break;
        }
        break;

    case TURN_SR:
        switch (casilla_inicial) {
        case '?':
            coste = 5;
            break;
        case 'A':
            coste = 16;
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

void ComportamientoRescatador::visualizaPlan(const EstadoRes &st, const std::vector<Action> &plan) {
    anularMatriz(mapaConPlan);
    EstadoRes cst = st;

    for (const auto &accion : plan) {
        switch (accion) {
        case RUN:
            cst.fila += 2 * offset_orientacion[cst.brujula].first;
            cst.col += 2 * offset_orientacion[cst.brujula].second;
            mapaConPlan[cst.fila][cst.col] = 3;
            break;
        case WALK:
            cst.fila += offset_orientacion[cst.brujula].first;
            cst.col += offset_orientacion[cst.brujula].second;
            mapaConPlan[cst.fila][cst.col] = 1;
            break;
        case TURN_SR:
            cst.brujula = (cst.brujula + 1) % 8;
            break;
        case TURN_L:
            cst.brujula = (cst.brujula + 6) % 8;
            break;
        default:
            std::exit(1);
            break;
        }
    }
}

struct Comparador {
    bool operator()(const NodoDijkstra &a, const NodoDijkstra &b) const {
        return a.coste > b.coste;
    }
};

auto ComportamientoRescatador::rescatadorDijkstra(const EstadoRes &inicio, const EstadoRes &final)
    -> std::vector<Action> {

    std::priority_queue<NodoDijkstra, std::vector<NodoDijkstra>, Comparador> frontier;
    std::unordered_map<EstadoRes, int> coste_minimo;

    frontier.emplace(inicio, std::vector<Action>{}, 0);
    coste_minimo[inicio] = 0;

    while (!frontier.empty()) {
        const NodoDijkstra actual = frontier.top();
        frontier.pop();

        EstadoRes estado_actual = actual.estado;

        if (estado_actual.fila == final.fila && estado_actual.col == final.col) {
            return actual.secuencia;
        }

        if (mapaResultado[estado_actual.fila][estado_actual.col] == 'D') {
            estado_actual.zapatillas = true;
        }

        for (Action accion : {RUN, WALK, TURN_L, TURN_SR}) {
            EstadoRes nuevo = applyAction<2>(accion, estado_actual);

            if (nuevo.fila == estado_actual.fila && nuevo.col == estado_actual.col &&
                (accion == WALK || accion == RUN))
                continue;

            const int nuevo_coste = actual.coste + calcularCoste(accion, estado_actual);

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

template <int Nivel>
auto ComportamientoRescatador::applyAction(Action accion, const EstadoRes &st) -> EstadoRes {
    EstadoRes next = st;
    switch (accion) {
    case TURN_L:
        next.brujula = (st.brujula + 6) % 8;
        break;
    case TURN_SR:
        next.brujula = (st.brujula + 1) % 8;
        break;
    case WALK:
        if (casillaAccesibleRescatador<Nivel>(st, accion)) {
            next.fila += offset_orientacion[st.brujula].first;
            next.col += offset_orientacion[st.brujula].second;
        }
        break;
    case RUN:
        if (casillaAccesibleRescatador<Nivel>(st, accion)) {
            next.fila += 2 * offset_orientacion[st.brujula].first;
            next.col += 2 * offset_orientacion[st.brujula].second;
        }
        break;
    default:
        std::exit(1);
        break;
    }

    return next;
}

template <int Nivel>
auto ComportamientoRescatador::casillaAccesibleRescatador(const EstadoRes &st, Action accion)
    -> bool {
    auto esTransitableN2 = [&](std::size_t f2, std::size_t c2) -> bool {
        char terreno = mapaResultado[f2][c2];

        return terreno != 'P' && terreno != 'M' && terreno != 'B';
    };
    auto viablePorAlturaN2 = [&](int altura) -> bool {
        return std::abs(altura) < 2 || (st.zapatillas && abs(altura) < 3);
    };

    std::size_t f = st.fila + offset_orientacion[st.brujula].first;
    std::size_t c = st.col + offset_orientacion[st.brujula].second;

    if (accion == Action::RUN) {
        std::size_t fil_f = f + offset_orientacion[st.brujula].first;
        std::size_t col_f = c + offset_orientacion[st.brujula].second;

        if constexpr (Nivel == 4) {
            return (esTransitableN2(fil_f, col_f) && esTransitableN2(f, c) &&
                    viablePorAlturaN2(mapaCotas[st.fila][st.col] - mapaCotas[fil_f][col_f])) ||
                   (mapaResultado[fil_f][col_f] == '?' && esTransitableN2(f, c)) ||
                   (esTransitableN2(fil_f, col_f) && esTransitableN2(f, c) &&
                    mapaResultado[st.fila][st.col] == '?');
        }

        return (esTransitableN2(fil_f, col_f) && esTransitableN2(f, c) &&
                viablePorAlturaN2(mapaCotas[st.fila][st.col] - mapaCotas[fil_f][col_f])) ||
               mapaResultado[fil_f][col_f] == '?';
    }

    if constexpr (Nivel == 4) {
        return (esTransitableN2(f, c) &&
                viablePorAlturaN2(mapaCotas[st.fila][st.col] - mapaCotas[f][c])) ||
               mapaResultado[f][c] == '?' ||
               (mapaResultado[st.fila][st.col] == '?' && esTransitableN2(f, c));
    }
    return (esTransitableN2(f, c) &&
            viablePorAlturaN2(mapaCotas[st.fila][st.col] - mapaCotas[f][c])) ||
           mapaResultado[f][c] == '?';
}

/*  ╔════════════════════════════════════════════════════════╗
    ║                     Métodos nivel 4                    ║
    ╚════════════════════════════════════════════════════════╝ */

auto ComportamientoRescatador::rescatadorDijkstraDesconocido(
    const EstadoRes &inicio, const EstadoRes &final,
    const std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> &evitar)
    -> std::vector<Action> {

    std::priority_queue<NodoDijkstra, std::vector<NodoDijkstra>, Comparador> frontier;
    std::unordered_map<EstadoRes, int> coste_minimo;

    frontier.emplace(inicio, std::vector<Action>{}, 0);
    coste_minimo[inicio] = 0;

    while (!frontier.empty()) {
        const NodoDijkstra actual = frontier.top();
        frontier.pop();

        EstadoRes estado_actual = actual.estado;

        if (estado_actual.fila == final.fila && estado_actual.col == final.col) {
            return actual.secuencia;
        }

        if (mapaResultado[estado_actual.fila][estado_actual.col] == 'D') {
            estado_actual.zapatillas = true;
        }

        for (Action accion : {RUN, WALK, TURN_L, TURN_SR}) {
            EstadoRes nuevo = applyAction<2>(accion, estado_actual);

            if ((accion == WALK || accion == RUN) &&
                ((nuevo.fila == estado_actual.fila && nuevo.col == estado_actual.col) ||
                 evitar.count({nuevo.fila, nuevo.col}) > 0))
                continue;

            if (accion == RUN) {
                int f_mid = estado_actual.fila + offset_orientacion[estado_actual.brujula].first;
                int c_mid = estado_actual.col + offset_orientacion[estado_actual.brujula].second;
                if (evitar.count({f_mid, c_mid}) > 0)
                    continue;
            }

            const int nuevo_coste = actual.coste + calcularCoste(accion, estado_actual);

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

auto ComportamientoRescatador::rescatadorDijkstraDesesperado(
    const EstadoRes &inicio, const EstadoRes &final,
    const std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> &evitar)
    -> std::vector<Action> {

    std::priority_queue<NodoDijkstra, std::vector<NodoDijkstra>, Comparador> frontier;
    std::unordered_map<EstadoRes, int> coste_minimo;

    frontier.emplace(inicio, std::vector<Action>{}, 0);
    coste_minimo[inicio] = 0;

    while (!frontier.empty()) {
        const NodoDijkstra actual = frontier.top();
        frontier.pop();

        EstadoRes estado_actual = actual.estado;

        if (estado_actual.fila == final.fila && estado_actual.col == final.col) {
            return actual.secuencia;
        }

        if (mapaResultado[estado_actual.fila][estado_actual.col] == 'D' ||
            mapaResultado[estado_actual.fila][estado_actual.col] == '?') {
            estado_actual.zapatillas = true;
        }

        for (Action accion : {RUN, WALK, TURN_L, TURN_SR}) {
            EstadoRes nuevo = applyAction<4>(accion, estado_actual);

            if ((accion == WALK || accion == RUN) &&
                ((nuevo.fila == estado_actual.fila && nuevo.col == estado_actual.col) ||
                 evitar.count({nuevo.fila, nuevo.col}) > 0))
                continue;

            if (accion == RUN) {
                int f_mid = estado_actual.fila + offset_orientacion[estado_actual.brujula].first;
                int c_mid = estado_actual.col + offset_orientacion[estado_actual.brujula].second;
                if (evitar.count({f_mid, c_mid}) > 0)
                    continue;
            }

            const int nuevo_coste = actual.coste + calcularCoste(accion, estado_actual);

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
