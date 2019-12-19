//ex3
import ex3.OldMacCow;
import ex3.OldMacDuck;

public class ex3{
    public static void main( String[] args ) {
        OldMacCow maudine = new OldMacCow();
        OldMacCow pauline = new OldMacCow();
        maudine.moo();
        pauline.moo();

        OldMacDuck ferdinand = new OldMacDuck();
        ferdinand.quack();
    }
}
