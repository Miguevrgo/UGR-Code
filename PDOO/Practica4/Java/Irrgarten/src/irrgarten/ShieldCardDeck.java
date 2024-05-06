package irrgarten;

public class ShieldCardDeck extends CardDeck<Shield> { //TODO: Da error porque hay que cambiar todavia shield y Weapon
    //TODO: Preguntar por numeros magicos,etc
    private final int DECK_SIZE = 5;
    protected void addCards() {
        for (int i = 0; i < DECK_SIZE; ++i){
            this.addCard(new Shield(Dice.shieldPower(), Dice.usesLeft()));
        }
    }
    
}
