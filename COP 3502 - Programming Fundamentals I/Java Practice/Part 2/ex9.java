//ex9

public class ex9{
    public static void main(String[] args) {
        SphereCalc3 sc3 = new SphereCalc3();
        SphereCalc4 sc = new SphereCalc4(5);

        sc3.setRadius(5);
        if(sc3.getRadius() == sc.getRadius())
            System.out.println("Same radius");
        if(sc3.getSurfaceArea() == sc.getSurfaceArea())
            System.out.println("Same surface area");
        if(sc3.getVolume() == sc.getVolume())
            System.out.println("Same volume");

    }

}
