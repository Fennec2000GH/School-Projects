class Diamond:
    def __init__(self, size, border = "#", fill = "*"):
        self.size = int(size)
        if(self.size > 39):
            self.size = 39
        elif(self.size < 1):
            self.size = 1
        self.border = border
        self.fill = fill

    def GetSize(self):
        return self.size

    def Perimeter(self):
        return self.size * 4

    def Area(self):
        return round(pow(float(self.size), 2.0) * pow(3.0, 0.5) / 2, 2)

    def Grow(self):
        if(self.size < 39):
            self.size += 1

    def Shrink(self):
        if(self.size > 1):
            self.size -= 1

    def SetBorder(self, border):
        if(int(ord(border)) > 126 or int(ord(border) < 33)):
            self.border = "#"
        else:
            self.border = border

    def SetFill(self, fill):
        if(int(ord(fill)) > 126 or int(ord(fill)) < 33):
            self.fill = "*"
        else:
            self.fill = fill

    def Draw(self):
        for i in range(self.size):
            if(i == 0):
                print("%s%s" % (" " * int(self.size - 1), self.border))
            else:
                print("%s%s%s%s" % (" " * int(self.size - 1 - i), self.border, (" %s" % self.fill) * int(i - 1), " %s" % self.border))
        for i in range(self.size - 1, 0, -1):
            if(i == 1):
                print("%s%s" % (" " * int(self.size - 1), self.border))
            else:
                print("%s%s%s%s" % (" " * int(self.size - i), self.border, (" %s" % self.fill) * int(i - 2), " %s" % self.border))
    def Summary(self):
        print("Size of diamond's side = %d units." % self.GetSize())
        print("Perimeter of diamond = %d units." % self.Perimeter())
        print("Area of diamond = %d units." % self.Area())
        print("Diamond looks like:")
        self.Draw()
