/**
 * @file GameState.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sanchez
 * @description This file contains a main class to test the game
 */

package irrgarten.main;

import irrgarten.Game;
import irrgarten.controller.Controller;
import irrgarten.UI.JFrameUI;


public class MainP5 {
    
    public static void main (String[] args) {
        
        final int NUMPLAYERS = 1;

        JFrameUI view = new JFrameUI();
        Game game = new Game(NUMPLAYERS);
        Controller controller = new Controller(game, view);

        controller.play();
    }
}