/**
 * @file Controller.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sanchez
 * @description This file contains the controller class 
 * 
 */

package irrgarten.controller;

import irrgarten.Directions;
import irrgarten.Game;
import irrgarten.UI.UI;


public class Controller {
    
    private Game game;
    private UI view;
    
    public Controller(Game game, UI view) {
        this.game = game;
        this.view = view;
    }
    
    public void play() {
        boolean endOfGame = false;
        while (!endOfGame) {
            view.showGame(game.getGameState()); 
            Directions direction = view.nextMove(); 
            endOfGame = game.nextStep(direction);
        }
        view.showGame(game.getGameState());        
    }
    
}
