/**
 * @file GameState.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sanchez
 * @description This file contains the GameState class, which provides methods
 * to represent the state of the game
 */

package irrgarten;

/**
 * This class is used to represent the state of the game
 */
public class GameState {
    private String labyrinth; 
    private String players;
    private String monsters;
    private int currentPlayer;
    private boolean winner;
    private String log;

    /**
     * Constructor for GameState
     * 
     * @param labyrinth
     * @param players
     * @param monsters
     * @param currentPlayer
     * @param winner
     * @param log 
     */
    public GameState(String labyrinth, String players, String monsters, int currentPlayer, boolean winner, String log) {
        this.labyrinth = labyrinth;
        this.players = players;
        this.monsters = monsters;
        this.currentPlayer = currentPlayer;
        this.winner = winner;
        this.log = log;
    }

    public String getLabyrinth() {
        return this.labyrinth;
    }

    public String getPlayers() {
        return this.players;
    }

    public String getMonsters() {
        return this.monsters;
    }

    public int getCurrentPlayer() {
        return this.currentPlayer;
    }

    public boolean isWinner() {
        return this.winner;
    }

    public String getLog() {
        return this.log;
    }


}
