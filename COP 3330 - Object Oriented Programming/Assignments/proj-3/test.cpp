#include <iostream>
#include "bigint.h"
#include "bigint.cpp"

using namespace std;

void test1()
{
  bigint x;
  bigint y;

  if (x == y)
      cout << x << " is equal to " << y << "." << endl;
  if (x != y)
      cout << x << " is not equal to " << y << "." << endl;
  if (x > y)
      cout << x << " is larger than " << y << "." << endl;
  if (x >= y)
      cout << x << " is larger than or equal to " << y << "." << endl;
  if (x < y)
      cout << x << " is smaller than " << y << "." << endl;
  if (x <= y)
      cout << x << " is smaller than or equal to " << y << "." << endl;

  cout << endl;

  bigint x1(123456789, 111, 111, 111, 111);
  bigint y1(111111111, 111, 111, 111, 111);

  if (x1 == y1)
      cout << x1 << " is equal to " << y1 << "." << endl;
  if (x1 != y1)
      cout << x1 << " is not equal to " << y1 << "." << endl;
  if (x1 > y1)
      cout << x1 << " is larger than " << y1 << "." << endl;
  if (x1 >= y1)
      cout << x1 << " is larger than or equal to " << y1 << "." << endl;
  if (x1 < y1)
      cout << x1 << " is smaller than " << y1 << "." << endl;
  if (x1 <= y1)
      cout << x1 << " is smaller than or equal to " << y1 << "." << endl;

  cout << endl;

  bigint x2(999999999, 999999999, 999999999, 20);

  cout << x2 << "+1 = " << x2 + 1 << endl;

  bigint y2(000000000, 000000000, 000000000, 000000000, 000000001);

  cout << y2 << "-1 = " << y2-1 << endl;

  cout << "x1 + x2 - y2 + 1 = " << x1+x2-y2+1 << endl;

  cout << endl;

  for (int i=0; i<3; i++)
  {
    bigint x, y;
    cin >> x >> y;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    cout << "x+y=" << x+y << endl;
    cout << "x-y=" << x-y << endl;
  }
}

int main()
{
  test1();

  return 0;
}
