/**
 * @file GameState.java
 * @author Miguel Angel De la Vega Rodríguez
 * @description This file contains a main class to test the game
 */

package irrgarten.main;

import irrgarten.Game;
import irrgarten.controller.Controller;
import irrgarten.UI.TextUI;


public class MainP3 {
    
    public static void main (String[] args) {
        
        final int NUMPLAYERS = 2;

        TextUI view = new TextUI();
        Game game = new Game(NUMPLAYERS);
        Controller controller = new Controller(game, view);

        controller.play();
    }
}