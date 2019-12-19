//ex11
import ex11.FieldAccess;

public class ex11{
    public static void main(String[] args) {
        FieldAccess j = new FieldAccess("Robert", "Parker", "Butch");
        System.out.println(j.getFullName());

        j.setLast("Elliot");
        j.setFirst("Samuel");
        j.setNick("Sam");
        System.out.println(j.getFullName());

        j.first = "Avery";
        // j.last = "Markham";
        System.out.println(j.getNick());

    }

}
