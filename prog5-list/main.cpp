#include <iostream>
#include "List.h"
#include <iomanip>

using namespace std;

int main()
{
    List<int> tList;

    tList.PushFront(12);
    tList.PushFront(22);
    tList.PushFront(32);
    tList.PushFront(42);
    tList.PushFront(52);
    tList.PushFront(62);
    cout << "Size: " << tList.Size() << " // 6\nFront: " << tList.Front() <<
        " // 62\nAt: " << tList.At(0) << " // 42";


    tList.PushBack(13);
    tList.PushBack(23);
    tList.PushBack(33);
    tList.PushBack(43);
    tList.PushBack(53);
    cout << "\nSize: " << tList.Size() << " // 11\nBack: " << tList.Back() <<
        " // 53\nAt: " << tList.At(5) << " // 13\n\n";
    
    for (List<int>::Iterator iter = tList.Begin(); !iter.IsEqual(tList.End()); iter.Next())
    {
        // REMEMBER THIS LOOP!  It is the grown-up version of "for( int i = 0; i < count; i++ )"
        cout << "List Data       " << iter.GetData() << " " << endl;
    }
    return 0;
}
