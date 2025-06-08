#ifndef __AI_PLAYER_H__
#define __AI_PLAYER_H__

#include "../../include/model/Attributes.h"
#include "../../include/model/Heuristic.h"
#include "../../include/model/Player.h"
#include <unordered_map>

class HeuristicaDistancia : public Heuristic {
  protected:
    virtual float getHeuristic(const Parchis &estado, int jugador) const;
};

class HeuristicaAgresiva : public Heuristic {
  protected:
    virtual float getHeuristic(const Parchis &estado, int jugador) const;
};

class ValoracionTest : public Heuristic {
  public:
    virtual float getHeuristic(const Parchis &estado, int jugador) const;
};

struct TTEntry {
    float value; // Valor almacenado
    int depth;   // Profundidad a la que se evaluó
    enum Flag : uint8_t { EXACT, LOWER, UPPER } flag;
};

class AIPlayer : public Player {
  protected:
    // Id identificativo del jugador
    const int id;
    mutable std::unordered_map<std::size_t, TTEntry> tt;
    std::size_t hash(const Parchis &s) const;

  public:
    /**
     * @brief Constructor de un objeto AIPlayer
     *
     * @param name Nombre del jugador
     */
    inline AIPlayer(const string &name) : Player(name), id(1) {};

    /**
     * @brief Constructor de un objeto AIPlayer
     *
     * @param name Nombre  del jugador
     * @param id Id del jugador
     */
    inline AIPlayer(const string &name, const int id) : Player(name), id(id) {};

    /**
     * @brief Función que percibe el el parchís y al jugador actual.
     * Asigna el tablero en actual y el id del jugador.
     *
     * @param p Instancia Parchis que se quiere percibir
     */
    inline virtual void perceive(Parchis &p) { Player::perceive(p); }

    /**
     * @brief Función abstracta que define el movimiento devuelto por el jugador.
     * Llama a la función movePiece con el valor asignado a los parámetros pasados
     * por referencia.
     *
     * @return true
     * @return false
     */
    virtual bool move();

    /**
     * @brief Función que se encarga de decidir el mejor movimiento posible a
     * partir del estado actual del tablero. Asigna a las variables pasadas por
     * referencia el valor de color de ficha, id de ficha y dado del mejor movimiento.
     *
     * @param c_piece Color de la ficha
     * @param id_piece Id de la ficha
     * @param dice Número de dado
     */
    virtual void think(color &c_piece, int &id_piece, int &dice) const;

    /**
     * @brief Método que determina si el player es inteligente (decide el mejor movimiento)
     * o no. True para AIPlayer.
     *
     * @return true
     * @return false
     */
    inline virtual bool canThink() const { return true; }

  private:
    template <int alg_id>
    auto eligeMovimiento(const Parchis &estado, int jugador, int profundidad_max, color &c_piece, int &id_piece,
                         int &dice, Heuristic *heuristic) const -> float;

    float minimax(const Parchis &estado, int jugador, int profundidad, Heuristic *heuristic) const;

    float alphaBeta(const Parchis &estado, int jugador, int profundidad, Heuristic *heuristic, float alpha,
                    float beta) const;
    float alphaBetaProb(const Parchis &estado, int jugador, int profundidad, Heuristic *heuristic, float alpha,
                        float beta) const;

    float alphaBetaTT(const Parchis &estado, int jugador, int profundidad, Heuristic *heuristic, float alpha,
                      float beta) const;

    float alphaBetaTTL(const Parchis &estado, int jugador, int profundidad, Heuristic *heuristic, float alpha,
                       float beta) const;

    float iterativeDeepening(const Parchis &estado, int jugador, color &c_piece, int &id_piece, int &dice,
                             Heuristic *heuristic) const;
};

#endif
