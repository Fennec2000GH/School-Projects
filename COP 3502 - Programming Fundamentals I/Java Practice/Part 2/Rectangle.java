//Rectangle
package ex12; 

public class Rectangle{
    private int length, width;

    public Rectangle() {
        length = width = 0;
    }

    public Rectangle(int l, int w){
        length = l;
        width = w;
    }

    public int getArea(){
        return length*width;
    }
}
