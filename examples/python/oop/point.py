
class Point:

  def __init__(self, newx, newy):
    self.x = newx
    self.y = newy
    
  def display(self):
    print("(%d,%d)" % (self.x, self.y))
    
  def moveTo(self, newx, newy):
    self.x = newx
    self.y = newy

#----------- Main program -------------------

if __name__ == "__main__":
    p1 = Point(5, 10)
    p2 = Point(20, 30)

    p1.display()
    p2.display()

    p1.moveTo(-5, -10)
    p1.display()

    Point.display(p1)  # alternate method call syntax

    line = [p1, p2]  # a list of points
    for p in line:
      p.display()

