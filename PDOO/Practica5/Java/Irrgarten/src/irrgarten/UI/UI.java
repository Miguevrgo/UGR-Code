/**
 * @file UI.java
 * @author Miguel Angel De la Vega Rodríguez
 * @author Alberto De la Vera Sanchez
 * @description This file contains an interface for UI
 */

package irrgarten.UI;

import irrgarten.Directions;
import irrgarten.GameState;


public interface UI {
    public Directions nextMove();
    public void showGame(GameState gameState);
}
