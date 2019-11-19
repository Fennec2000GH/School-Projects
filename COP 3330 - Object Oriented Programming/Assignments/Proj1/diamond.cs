using System;

namespace Space{
    class Diamond{
        //VARIABLES
        private int size;
        private char border, fill;

        //CONSTRUCTOR
        public Diamond(int size, char border = '#', char fill = '*'){
            if(size < 1)
                this.size = 1;
            else if(size > 39)
                this.size = 39;
            else
                this.size = size;
            if(Convert.ToInt16(border) < 33)
                this.border = '!';
            else if(Convert.ToInt16(border) > 126)
                this.border = '~';
            else
                this.border = border;
            if(Convert.ToInt16(fill) < 33)
                this.fill = '!';
            else if(Convert.ToInt16(fill) > 126)
                this.fill = '~';
            else
                this.fill = fill;
        }

        public int GetSize(){
            return size;
        }
        public int Perimeter(){
            return size * 4;
        }
        public double Area(){
            return Math.Pow(size, 2) * Math.Pow(3, 0.5) / 4;
        }
        public void Grow(){
            if(size < 39)
                ++size;
            return;
        }
        public void Shrink(){
            if(size > 1)
                --size;
            return;
        }
        public void SetBorder(char border){
            if(Convert.ToInt16(border) > 126 || Convert.ToInt16(border) < 33)
                this.border = '#';
            else
                this.border = border;
            return;
        }
        public void SetFill(char fill){
            if(Convert.ToInt16(fill) > 126 || Convert.ToInt16(fill) < 33)
                this.border = '*';
            else
                this.fill = fill;
            return;
        }
        public void Summary(){
            Console.WriteLine("Size of diamond's side = {0} units.", GetSize());
            Console.WriteLine("Perimeter of diamond = {0} units.", Perimeter());
            Console.WriteLine("Area of diamond = {0} units.", Area());
            Console.WriteLine("Diamond looks like:\n");
            //Draw();
            return;
        }
        public void Draw(){
            for(int i = 1; i <= size; i++){
                for(int left = 1; left <= size - i; left++)
                    Console.Write(" ");
                if(i == 1)
                    Console.WriteLine(border);
                else{
                    Console.Write(border);
                    for(int mid = 1; mid <= i - 2; mid++)
                        Console.Write(" {0}", fill);
                    Console.WriteLine(" {0}", border);
                }
            }
            for(int i = size - 1; i >= 1; i--){
                for(int left = 1; left <= size - i; left++)
                    Console.Write(" ");
                if(i == 1)
                    Console.WriteLine(border);
                else{
                    Console.Write(border);
                    for(int mid = 1; mid <= i - 2; i++)
                        Console.Write(" {0}", border);
                    Console.WriteLine(" {0}", border);
                }
            }

            return;
        }

    }
    class DiamondExecute{
        public static void Main(string[] args){
            // create some Diamonds
            Diamond d1 = new Diamond(-5);
            Diamond d2 = new Diamond(7,'^');
            Diamond d3 = new Diamond(12,'X','O');
            Diamond d4 = new Diamond(50,'$','o');

            // display original Diamonds
            Console.WriteLine("d1 has size = {0} units.", d1.GetSize());
            d1.Draw();
            Console.WriteLine("\nd2 has size = {0} units.", d2.GetSize());
            d2.Draw();
            Console.WriteLine("\nd3 has size = {0} units.", d3.GetSize());
            d3.Draw();
            Console.WriteLine("\nd4 has size = {0} units.", d4.GetSize());
            d4.Draw();
            Console.WriteLine("");

            d1.Shrink(); // demonstrate shrink
            d2.Shrink();
            d3.Grow(); // and grow
            d4.Grow();
            Console.WriteLine("d1 now has size = {0} units.", d1.GetSize());
            Console.WriteLine("d2 now has size = {0} units.", d2.GetSize());
            Console.WriteLine("d3 now has size = {0} units.", d3.GetSize());
            Console.WriteLine("d4 now has size = {0} units.", d4.GetSize());

            // demonstrate perimeter
            Console.WriteLine("d2 has perimeter = {0} units.", d2.Perimeter());
            Console.WriteLine("d3 has perimeter = {0} units.", d3.Perimeter());
            // and area
            Console.WriteLine("d2 has area = {0} square units.\n", d2.Area());
            Console.WriteLine("d3 has area = {0} square units.\n", d3.Area());

            d1.Draw();
            d1.Grow();               // show that fill character
            Console.WriteLine("d1 grows:");   // appears only when size
            d1.Draw();               // is at least 3
            d1.Grow();
            Console.WriteLine("... and grows:");
            d1.Draw();
            Console.WriteLine("");

            d1 = d2; // demonstrate the default overload of the
            // assignment operator
            Console.WriteLine("d1 now has size = {0} units.", d1.GetSize());
            d1.Draw();

            // demonstrate the changing of border and fill characters
            d2.SetBorder('@');
            d2.SetFill('-');
            Console.WriteLine("d2 now looks like:");
            d2.Draw();
            Console.WriteLine("");
            d2.SetBorder('\n');	 // illegal border
            d2.SetFill('\a');	 // illegal fill
            Console.WriteLine("d2 now looks like:");
            d2.Draw();
            Console.WriteLine("");

            Console.WriteLine("\nHere is a summary on d3:"); // demonstrate summary
            d3.Summary();
            
        }
    }
}
