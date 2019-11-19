package proj1;
import java.lang.Math;

public class diamond 
{
    //CONSTRUCTORS
    public diamond(int size)
    {
        if(size > 39)
            this.size = 39;
        else if(size < 1)
            this.size = 1;
        else
            this.size = size;
    }

    public diamond(int size, char border)
    {
        this.size = size;
        this.border = border;
    }

    public diamond(int size, char border, char fill)
    {
        this.size = size;
        this.border = border;
        this.fill = fill;
    }

    //FUNCTIONS
    int GetSize()
    {
        return size;
    }

    int Perimeter()
    {
        return size * 4;
    }

    double Area()
    {
        return Math.pow(size, 2) * Math.pow(3, 0.5) / 2;
    }

    void Grow()
    {
        if(size < 39)
            ++size;
        return;
    }

    void Shrink()
    {
        if(size > 1)
            --size;
        return;
    }

    void SetBorder(char border)
    {
        if(border > 126 || border < 33)
            this.border = '#';
        else
            this.border = border;
        return;
    }

    void SetFill(char fill)
    {
        if(fill > 126 || fill < 33)
            this.fill = '*';
        else
            this.fill = fill;
        return;
    }

    void Draw()
    {
        for(int row = 1; row <= size * 2 - 1; ++row)
        {
            for(int space = 1; space <= Math.abs(size - row) * 2; ++space)
                System.out.print(" ");
            System.out.print(border + " ");
            for(int inside = 1; inside <= size - Math.abs(size - row) - 1; ++inside)
                System.out.print(" " + fill);
            System.out.print(border + "\n");
        }
    }

    void Summary()
    {
        System.out.println("Size:\t" + size);
        System.out.println("Perimeter:\t" + Perimeter());
        System.out.println("Area:\t" + Area());
        return;
    }

    //DATA MEMBERS
    private int size;
    private char border, fill;

    //main program
    public static void main(String[] args)
    {
        // create some Diamonds
        diamond d1 = new diamond(-5);
        diamond d2 = new diamond(7,'^');
        diamond d3 = new diamond(12,'X','O');
        diamond d4 = new diamond(50,'$','o');

        // display original Diamonds
        System.out.print("d1 has size = " + d1.GetSize() + " units.\n");
        d1.Draw();
        System.out.println("d2 has size = " + d2.GetSize() + " units.\n");
        d2.Draw();
        System.out.println("d3 has size = " + d3.GetSize() + " units.\n");
        d3.Draw();
        System.out.println("d4 has size = " + d4.GetSize() + " units.\n");
        d4.Draw();
        System.out.print("\n");

        d1.Shrink(); // demonstrate shrink
        d2.Shrink();
        d3.Grow(); // and grow
        d4.Grow();
        System.out.println("d1 now has size = " + d1.GetSize() + " units.\n");
        System.out.print("d2 now has size = " + d2.GetSize() + " units.\n");
        System.out.print("d3 now has size = " + d3.GetSize() + " units.\n");
        System.out.print("d4 now has size = " + d4.GetSize() + " units.\n");

        // demonstrate perimeter
        System.out.print("d2 has perimeter = " + d2.Perimeter() + " units.\n");
        System.out.print("d3 has perimeter = " + d3.Perimeter() + " units.\n");
        // and area
        System.out.print("d2 has area = " + d2.Area() + " square units.\n\n");
        System.out.print("d3 has area = " + d3.Area() + "square units.\n\n");

        d1.Draw();
        d1.Grow();               // show that fill character
        System.out.print("d1 grows:\n");    // appears only when size
        d1.Draw();               // is at least 3
        d1.Grow();
        System.out.print("... and grows:\n");
        d1.Draw();
        System.out.print("\n");

        d1 = d2; // demonstrate the default overload of the
        // assignment operator
        System.out.print("d1 now has size = " + d1.GetSize() + " units.\n");
        d1.Draw();

        // demonstrate the changing of border and fill characters
        d2.SetBorder('@');
        d2.SetFill('-');
        System.out.print("d2 now looks like:\n");
        d2.Draw();
        System.out.print("\n");
        d2.SetBorder('\n');	 // illegal border
        //d2.SetFill('\a');	 // illegal fill
        System.out.print("d2 now looks like:\n");
        d2.Draw();
        System.out.print("\n");

        System.out.println("Here is a summary on d3:\n");  // demonstrate summary
        d3.Summary();

    }
}
