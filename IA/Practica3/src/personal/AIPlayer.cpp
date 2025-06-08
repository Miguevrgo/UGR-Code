#include "AIPlayer.h"
#include "../../include/model/Parchis.h"
#include "model/NodeCounter.h"
#include "model/Player.h"
#include <functional>
#include <sstream>
#include <vector>

const int INF = 2 << 28;
const int GANA = INF >> 3;
const int PIERDE = -GANA;

const int NUM_PIECES = 2;
const int PROFUNDIDAD_MINIMAX = 5;   // Profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALPHABETA = 7; // Profundidad para la poda Alpha_Beta
const float EPSILON = 5;             // Umbral de tolerancia poda Probabilistica

bool AIPlayer::move() {
    cout << COUT_ORANGE_BOLD << "Realizo un movimiento automatico" << COUT_NOCOLOR << endl;

    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    cout << COUT_ORANGE_BOLD << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << COUT_NOCOLOR
         << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

int fichasEnMeta(const Parchis &estado) {
    int fichas = 0;

    for (int jugador = 0; jugador < 2; ++jugador) {
        const auto &colores = estado.getPlayerColors(jugador);
        for (const auto &color : colores) {
            fichas += estado.piecesAtGoal(color);
        }
    }

    return fichas;
}

void AIPlayer::think(color &c_piece, int &id_piece, int &dice) const {
    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    HeuristicaDistancia distancia;
    HeuristicaAgresiva agresiva;
    ValoracionTest val;

    switch (id) {
    case 0: // Test Poda
        valor = eligeMovimiento<0>(*actual, jugador, PROFUNDIDAD_ALPHABETA, c_piece, id_piece, dice, &val);
        break;
    case 1: // Mejor: Poda AlphaBeta + Ordenacion + TT + Ramificacion ++ Late Move Reductions
        valor = eligeMovimiento<1>(*actual, jugador, PROFUNDIDAD_ALPHABETA, c_piece, id_piece, dice, &agresiva);
        tt.clear();
        break;
    case 2: // Poda AlphaBeta
        valor = eligeMovimiento<2>(*actual, jugador, PROFUNDIDAD_ALPHABETA, c_piece, id_piece, dice, &distancia);
        break;
    case 3: // Poda AlphaBeta factor ramificacion
        valor = eligeMovimiento<3>(*actual, jugador, PROFUNDIDAD_ALPHABETA, c_piece, id_piece, dice, &distancia);
        break;
    case 4: // Poda AlphaBeta con ordenacion
        valor = eligeMovimiento<4>(*actual, jugador, PROFUNDIDAD_ALPHABETA, c_piece, id_piece, dice, &distancia);
        break;
    case 5: // Poda AlphaBeta Probabilistica
        valor = eligeMovimiento<5>(*actual, jugador, PROFUNDIDAD_ALPHABETA, c_piece, id_piece, dice, &distancia);
        break;
    case 6: // Poda AlphaBeta con ordenacion + ramificacion
        valor = eligeMovimiento<6>(*actual, jugador, PROFUNDIDAD_ALPHABETA, c_piece, id_piece, dice, &distancia);
        break;
    case 7: // Primera Mejor: Poda AlphaBeta + iterativeDeepening + ramificacion + ordenacion + TT
        if ((*actual).getTurn() > 35) {
            valor = iterativeDeepening(*actual, jugador, c_piece, id_piece, dice, &distancia);
        } else {
            valor =
                eligeMovimiento<7>(*actual, jugador, PROFUNDIDAD_ALPHABETA - 1, c_piece, id_piece, dice, &distancia);
            tt.clear();
        }
        break;
    case 8: // Poda AlphaBeta iterativeDeepening
        valor = iterativeDeepening(*actual, jugador, c_piece, id_piece, dice, &distancia);
        break;
    default:
        exit(1);
        break;
    }
}

float HeuristicaDistancia::getHeuristic(const Parchis &estado, int jugador) const {
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;
    int score = 0;

    if (ganador == jugador) {
        return GANA;
    } else if (ganador == oponente) {
        return PIERDE;
    }

    for (auto &color : estado.getPlayerColors(jugador)) {
        for (int j = 0; j < NUM_PIECES; j++) {
            score -= 3 * estado.distanceToGoal(color, j);
            score += 5 * estado.isSafePiece(color, j);
        }

        score += estado.piecesAtGoal(color) * 50;
        score -= estado.piecesAtHome(color) * 40;
    }

    for (auto &color : estado.getPlayerColors(oponente)) {
        for (int j = 0; j < NUM_PIECES; j++) {
            score += 3 * estado.distanceToGoal(color, j);
            score -= 5 * estado.isSafePiece(color, j);
        }

        score -= estado.piecesAtGoal(color) * 50;
        score += estado.piecesAtHome(color) * 40;
    }

    return score;
}

float HeuristicaAgresiva::getHeuristic(const Parchis &estado, int jugador) const {
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;
    int score = 0;

    if (ganador == jugador) {
        return GANA;
    } else if (ganador == oponente) {
        return PIERDE;
    }

    for (const auto &color : estado.getPlayerColors(jugador)) {
        for (int i = 0; i < NUM_PIECES; ++i) {
            score += 15 * (estado.getBoard().getPiece(color, i).get_box().type == final_queue);
            score += 20 * estado.isSafePiece(color, i);
            score -= 50 * (estado.eatenPiece().first == color);
            score -= estado.distanceToGoal(color, i);
        }

        score -= 10 * estado.piecesAtHome(color);
        score += 20 * estado.piecesAtGoal(color);
    }

    for (const auto &color : estado.getPlayerColors(oponente)) {
        for (int i = 0; i < NUM_PIECES; ++i) {
            score -= 15 * (estado.getBoard().getPiece(color, i).get_box().type == final_queue);
            score -= 20 * estado.isSafePiece(color, i);
            score += 50 * (estado.eatenPiece().first == color);
            score += estado.distanceToGoal(color, i);
        }

        score += 10 * estado.piecesAtHome(color);
        score -= 20 * estado.piecesAtGoal(color);
    }

    return score;
}

template <int alg_id>
float AIPlayer::eligeMovimiento(const Parchis &estado, int jugador, int profundidad_max, color &c_piece, int &id_piece,
                                int &dice, Heuristic *heuristic) const {
    auto hijos = estado.getChildrenList();

    if (hijos.begin() == hijos.end()) {
        c_piece = estado.getCurrentColor();
        id_piece = SKIP_TURN;
        dice = 0;
        return heuristic->evaluate(estado, jugador);
    }

    float mejor_valor = -INF;

    if constexpr (alg_id == 3 || alg_id == 6 || alg_id == 7 || alg_id == 1) { // Factor ramificacion
        if (hijos.size() <= 2) {
            if (fichasEnMeta(estado) >= 2) {
                profundidad_max += 4;
            } else if (fichasEnMeta(estado) >= 1) {
                profundidad_max += 3;
            } else {
                profundidad_max += 2;
            }
        } else if (hijos.size() <= 7) {
            if (fichasEnMeta(estado) >= 2) {
                profundidad_max += 3;
            } else if (fichasEnMeta(estado) >= 1) {
                profundidad_max += 2;
            } else {
                profundidad_max += 1;
            }
        } else if (hijos.size() <= 16) {
            profundidad_max += 1;
        }

        if (fichasEnMeta(estado) >= 4) {
            profundidad_max += 1;
        }
        if (fichasEnMeta(estado) >= 5) {
            profundidad_max += 1;
        }
    }

    if constexpr (alg_id == 1 || alg_id == 4 || alg_id == 6 || alg_id == 7) { // Ordenacion
        std::sort(hijos.begin(), hijos.end(), [&](const auto &a, const auto &b) {
            return heuristic->evaluate(*a, jugador) > heuristic->evaluate(*b, jugador);
        });
    }

    for (auto &hijo : hijos) {
        if (NodeCounter::isLimitReached()) {
            break;
        }
        float valor;

        if constexpr (alg_id == 0 || alg_id == 2) { // Alpha Beta
            valor = alphaBeta(*hijo, jugador, profundidad_max - 1, heuristic, -INF, INF);
        } else if constexpr (alg_id == 1) { // Ramificacion
            valor = alphaBetaTTL(*hijo, jugador, profundidad_max - 1, heuristic, -INF, INF);
        } else if constexpr (alg_id == 3) { // Ramificacion
            valor = alphaBeta(*hijo, jugador, profundidad_max - 1, heuristic, -INF, INF);
        } else if constexpr (alg_id == 4) { // Ordenacion
            valor = alphaBeta(*hijo, jugador, profundidad_max - 1, heuristic, -INF, INF);
        } else if constexpr (alg_id == 5) { // Poda Probabilistica
            valor = alphaBetaProb(*hijo, jugador, profundidad_max - 1, heuristic, -INF, INF);
        } else if constexpr (alg_id == 6) { // Ordenacion + Ramificacion
            valor = alphaBeta(*hijo, jugador, profundidad_max - 1, heuristic, -INF, INF);
        } else if constexpr (alg_id == 7) { // Ordenacion + Ramificacion + TT
            valor = alphaBetaTT(*hijo, jugador, profundidad_max - 1, heuristic, -INF, INF);
        }

        if (NodeCounter::isLimitReached()) {
            if (mejor_valor == -INF) {
                mejor_valor = heuristic->evaluate(*hijos[0], jugador);
                c_piece = hijos[0].getMovedColor();
                id_piece = hijos[0].getMovedPieceId();
                dice = hijos[0].getMovedDiceValue();
            }
            break;
        }

        if (valor > mejor_valor) {
            mejor_valor = valor;
            c_piece = hijo.getMovedColor();
            id_piece = hijo.getMovedPieceId();
            dice = hijo.getMovedDiceValue();
        }
    }

    return mejor_valor;
}

float AIPlayer::alphaBeta(const Parchis &estado, int jugador, int profundidad, Heuristic *heuristic, float alpha,
                          float beta) const {
    if (profundidad == 0 || estado.gameOver()) {
        return heuristic->evaluate(estado, jugador);
    }

    auto hijos = estado.getChildren();

    float valor;
    if (estado.getCurrentPlayerId() == jugador) {
        valor = -INF;
        for (auto &hijo : hijos) {
            if (NodeCounter::isLimitReached()) {
                break;
            }

            valor = std::max(valor, alphaBeta(hijo, jugador, profundidad - 1, heuristic, alpha, beta));
            alpha = std::max(valor, alpha);

            if (alpha >= beta) {
                break; // beta cutoff
            }
        }
    } else {
        valor = INF;
        for (auto &hijo : hijos) {
            if (NodeCounter::isLimitReached()) {
                break;
            }

            valor = std::min(valor, alphaBeta(hijo, jugador, profundidad - 1, heuristic, alpha, beta));
            beta = std::min(valor, beta);

            if (alpha >= beta) {
                break; // alpha cutoff
            }
        }
    }

    return valor;
}

float AIPlayer::alphaBetaProb(const Parchis &estado, int jugador, int profundidad, Heuristic *heuristic, float alpha,
                              float beta) const {
    if (profundidad == 0 || estado.gameOver()) {
        return heuristic->evaluate(estado, jugador);
    }

    auto hijos = estado.getChildren();

    float valor;
    if (estado.getCurrentPlayerId() == jugador) {
        valor = -INF;
        for (auto &hijo : hijos) {
            if (NodeCounter::isLimitReached()) {
                break;
            }

            valor = std::max(valor, alphaBetaProb(hijo, jugador, profundidad - 1, heuristic, alpha, beta));
            alpha = std::max(valor, alpha);

            if (alpha >= beta || (beta - alpha) < EPSILON) {
                break; // beta cutoff
            }
        }
    } else {
        valor = INF;
        for (auto &hijo : hijos) {
            if (NodeCounter::isLimitReached()) {
                break;
            }

            valor = std::min(valor, alphaBetaProb(hijo, jugador, profundidad - 1, heuristic, alpha, beta));
            beta = std::min(valor, beta);

            if (alpha >= beta || (beta - alpha) < EPSILON) {
                break; // alpha cutoff
            }
        }
    }

    return valor;
}

std::size_t AIPlayer::hash(const Parchis &s) const {
    std::ostringstream ss;

    ss << s.getCurrentPlayerId() << '|';

    for (color c : Parchis::game_colors) {
        const auto &vec = s.getBoard().getPieces(c);
        for (int i = 0; i < (int)vec.size(); ++i) {
            const Box &b = vec[i].get_box();
            ss << (int)c << ':' << i << ':' << b.num << ',' << (int)b.type << ',' << (int)b.col << '|';
        }
    }

    return std::hash<std::string>{}(ss.str());
}

float AIPlayer::alphaBetaTT(const Parchis &estado, int jugador, int profundidad, Heuristic *heuristic, float alpha,
                            float beta) const {
    auto key = hash(estado);
    auto it = tt.find(key);
    if (it != tt.end() && it->second.depth >= profundidad) {
        switch (it->second.flag) {
        case TTEntry::EXACT:
            return it->second.value;
        case TTEntry::LOWER:
            alpha = std::max(alpha, it->second.value);
            break;
        case TTEntry::UPPER:
            beta = std::min(beta, it->second.value);
            break;
        }
        if (alpha >= beta)
            return it->second.value;
    }

    if (profundidad == 0 || estado.gameOver())
        return heuristic->evaluate(estado, jugador);

    bool maximizing = (estado.getCurrentPlayerId() == jugador);
    float best = maximizing ? -INF : INF;
    float old_alpha = alpha;

    for (auto &hijo : estado.getChildrenList()) {
        if (NodeCounter::isLimitReached()) {
            break;
        }

        float val = alphaBetaTT(*hijo, jugador, profundidad - 1, heuristic, alpha, beta);

        if (maximizing) {
            best = std::max(best, val);
            alpha = std::max(alpha, best);
        } else {
            best = std::min(best, val);
            beta = std::min(beta, best);
        }
        if (alpha >= beta)
            break;
    }

    TTEntry::Flag flag = TTEntry::EXACT;
    if (best <= alpha)
        flag = TTEntry::UPPER;
    else if (best >= beta)
        flag = TTEntry::LOWER;

    tt[key] = {best, profundidad, flag};
    return best;
}

float AIPlayer::alphaBetaTTL(const Parchis &estado, int jugador, int profundidad, Heuristic *heuristic, float alpha,
                             float beta) const {
    auto key = hash(estado);
    auto it = tt.find(key);
    if (it != tt.end() && it->second.depth >= profundidad) {
        switch (it->second.flag) {
        case TTEntry::EXACT:
            return it->second.value;
        case TTEntry::LOWER:
            alpha = std::max(alpha, it->second.value);
            break;
        case TTEntry::UPPER:
            beta = std::min(beta, it->second.value);
            break;
        }
        if (alpha >= beta)
            return it->second.value;
    }

    if (profundidad == 0 || estado.gameOver())
        return heuristic->evaluate(estado, jugador);

    float best;
    bool maximizing = (estado.getCurrentPlayerId() == jugador);
    best = maximizing ? -INF : INF;
    float original_alpha = alpha;

    auto hijos = estado.getChildren();
    int move_number = 0;

    for (auto &hijo : hijos) {
        if (NodeCounter::isLimitReached())
            break;

        float valor;
        bool do_lmr = profundidad >= 3 && move_number >= 3 && !hijo.isEatingMove();
        if (do_lmr) {
            int reduction = std::min(2, profundidad / 3);
            valor = alphaBetaTTL(hijo, jugador, profundidad - 1 - reduction, heuristic, alpha, beta);
            if ((maximizing && valor > alpha) || (!maximizing && valor < beta)) {
                valor = alphaBetaTTL(hijo, jugador, profundidad - 1, heuristic, alpha, beta);
            }
        } else {
            valor = alphaBetaTTL(hijo, jugador, profundidad - 1, heuristic, alpha, beta);
        }

        if (maximizing) {
            best = std::max(best, valor);
            alpha = std::max(alpha, best);
        } else {
            best = std::min(best, valor);
            beta = std::min(beta, best);
        }

        if (alpha >= beta)
            break;

        ++move_number;
    }

    TTEntry::Flag flag = TTEntry::EXACT;
    if (best <= original_alpha)
        flag = TTEntry::UPPER;
    else if (best >= beta)
        flag = TTEntry::LOWER;

    tt[key] = {best, profundidad, flag};
    return best;
}

float AIPlayer::iterativeDeepening(const Parchis &estado, int jugador, color &c_piece, int &id_piece, int &dice,
                                   Heuristic *heuristic) const {
    int profundidad = 1;
    float mejor_valor = -INF;

    color mejor_color;
    int mejor_id = SKIP_TURN;
    int mejor_dado = 0;

    while (std::abs(mejor_valor) != GANA) {
        tt.clear();
        auto hijos = estado.getChildrenList();

        if (profundidad == 1) {
            std::sort(hijos.begin(), hijos.end(), [&](const auto &a, const auto &b) {
                return heuristic->evaluate(*a, jugador) > heuristic->evaluate(*b, jugador);
            });
        }

        auto it = std::find_if(hijos.begin(), hijos.end(), [&](const auto &h) {
            return h.getMovedColor() == mejor_color && h.getMovedPieceId() == mejor_id &&
                   h.getMovedDiceValue() == mejor_dado;
        });
        if (it != hijos.end())
            std::rotate(hijos.begin(), it, it + 1);

        float mejor_valor_actual = -INF;
        color mejor_color_actual;
        int mejor_id_actual;
        int mejor_dado_actual;

        for (auto &hijo : hijos) {
            if (NodeCounter::isLimitReached()) {
                break;
            } else {
                float valor = alphaBetaTT(*hijo, jugador, profundidad - 1, heuristic, -INF, INF);

                if (valor > mejor_valor_actual) {
                    mejor_valor_actual = valor;
                    mejor_color_actual = hijo.getMovedColor();
                    mejor_id_actual = hijo.getMovedPieceId();
                    mejor_dado_actual = hijo.getMovedDiceValue();
                }
            }
        }

        if (NodeCounter::isLimitReached()) {
            break; // No actualizamos nada
        }

        mejor_valor = mejor_valor_actual;
        mejor_color = mejor_color_actual;
        mejor_id = mejor_id_actual;
        mejor_dado = mejor_dado_actual;

        profundidad++;
    }

    c_piece = mejor_color;
    id_piece = mejor_id;
    dice = mejor_dado;

    return mejor_valor;
}

float ValoracionTest::getHeuristic(const Parchis &estado, int jugador) const {
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    if (ganador == jugador) {
        return GANA;
    } else if (ganador == oponente) {
        return PIERDE;
    } else {
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        int puntuacion_jugador = 0;
        for (int i = 0; i < my_colors.size(); i++) {
            color c = my_colors[i];
            for (int j = 0; j < NUM_PIECES; j++) {
                if (estado.isSafePiece(c, j)) {
                    puntuacion_jugador++;
                } else if (estado.getBoard().getPiece(c, j).get_box().type == goal) {
                    puntuacion_jugador += 5;
                }
            }
        }

        int puntuacion_oponente = 0;
        for (int i = 0; i < op_colors.size(); i++) {
            color c = op_colors[i];
            for (int j = 0; j < NUM_PIECES; j++) {
                if (estado.isSafePiece(c, j)) {
                    puntuacion_oponente++;
                } else if (estado.getBoard().getPiece(c, j).get_box().type == goal) {
                    puntuacion_oponente += 5;
                }
            }
        }

        return puntuacion_jugador - puntuacion_oponente;
    }
}
