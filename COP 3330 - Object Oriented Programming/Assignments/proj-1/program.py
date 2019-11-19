 # program.cpp -- sample program to demonstrate the behavior of
 # 	  	  the Diamond class

from diamond import Diamond

if(__name__ == "__main__"):
    # create some Diamonds
    d1 = Diamond(-5)
    d2 = Diamond(7,'^')
    d3 = Diamond(12,'X','O')
    d4 = Diamond(50,'$','o')
    # display original Diamonds
    print("d1 has size = %d units." % d1.GetSize())
    d1.Draw()
    print("d2 has size = %d units." % d2.GetSize())
    d2.Draw()
    print("d3 has size = %d units." % d3.GetSize())
    d3.Draw()
    print("d4 has size = %d units." % d4.GetSize())
    d4.Draw()
    print("")

    d1.Shrink() # demonstrate shrink
    d2.Shrink()
    d3.Grow() # and grow
    d4.Grow()
    print("d1 now has size = %d units." % d1.GetSize())
    print("d2 now has size = %d units." % d2.GetSize())
    print("d3 now has size = %d units." % d3.GetSize())
    print("d4 now has size = %d units." % d4.GetSize())

     # demonstrate perimeter
    print("d2 has perimeter = %d units." % d2.Perimeter())
    print("d3 has perimeter = %d units." % d3.Perimeter())
     # and area
    print("d2 has area = %d square units.\n" % d2.Area())
    print("d3 has area = %d square units.\n" % d3.Area())

    d1.Draw()
    d1.Grow()               # show that fill character
    print("d1 grows:")       # appears only when size
    d1.Draw()               # is at least 3
    d1.Grow()
    print("... and grows:")
    d1.Draw()
    print("")

    d1 = d2 # demonstrate the default overload of the
    # assignment operator
    print("d1 now has size = %d units." % d1.GetSize())
    d1.Draw()

    # demonstrate the changing of border and fill characters
    d2.SetBorder("@")
    d2.SetFill('-')
    print("d2 now looks like:")
    d2.Draw()
    print("")
    d2.SetBorder('\n')	 # illegal border
    d2.SetFill('\a')	 # illegal fill
    print("d2 now looks like:")
    d2.Draw()
    print("")

    print("\nHere is a summary on d3:") # demonstrate summary
    d3.Summary()
