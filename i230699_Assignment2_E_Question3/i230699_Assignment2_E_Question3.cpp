#include <iostream>
#include "CAList.h"

int main()
{
    CAList tt, tt2, tt3;

    tt["OOP"] = "Dr.Ali";
    tt["OOP"] = "Mr.Shehryar";
    tt["OOP"] = "Ms.Hida";
    tt["OOP"] = "Mr.Shams";
    tt["DLD"] = "Mr.Amir";
    tt["DLD"] = "Mr.Shams";
    tt["DLD"] = "Dr.Mehwish";

    tt2["Algo"] = "Mr.Owais";
    tt2["OOP"] = "Dr.Omar";
    tt2["OOP"] = "Dr.Mehreen";
    tt2["OOP"] = "Dr.Nouman";
    tt2["OOP"] = "Dr.Aftab";
    tt2["OOP"] = "Mr.Shehryar";
    tt2["Pak Stds"] = "Mr.Ajmal";
    tt2["Pak Stds"] += "Ms.Gul";
    tt2["Pak Stds"] = "Ms.Memoona";
    tt2["Islamiat"] = "Dr.Tayab";
    tt2["Islamiat"] += "Ms.Sobia";
    tt2["Islamiat"] = "Mr.Usman";
    tt2["Islamiat"] += "Ms.Gul";
    tt2["Islamiat"] += "Mr.Anas";

   cout << tt << endl;

    cout << tt2 << endl;

    CAList tt5 = tt + tt2;

    cout << tt3 << endl;

    CAList tt4 = tt - tt2;

    tt2["a"] = "a";
    tt2["a"] = "b";
    tt2["a"] = "c";
    tt2["a"] = "d";
    tt2["a"] = "e";
    tt2["a"] = "f";
    tt2["a"] = "g";
    tt2["a"] = "h";

    tt2["b"] = "y";
    tt2["c"] = "z";
    tt2["d"] = "a";
    tt2["d"] = "c";
    tt2["d"] = "b";

    cout << tt4 << endl;
    cout << tt2 << endl;

    tt2["Islamiat"] -= "Ms.Gul";
    tt2["OOP"] -= "Dr.Nouman";
    tt2["OOP"] -= "Dr.Aftab";
    tt2["OOP"] -= "Mr.Shehryar";
    tt2["Pak Stds"] -= "Mr.Ajmal";
    tt2["Pak Stds"] -= "Ms.Gul";
    tt2["Pak Stds"] -= "Ms.Memoona";
    tt2["Islamiat"] -= "Dr.Tayab";
    tt2["Islamiat"] -= "Ms.Sobia";
    

    cout << tt2 << endl;

    CAList testing;
    testing["a"] = "a";
    testing["b"] = "a";
    testing["c"] = "a";
    testing["d"] = "a";
    testing["e"] = "a";
    testing["f"] = "a";
    testing["g"] = "a";
    testing["h"] = "a";

    cout << testing << endl;

    testing["a"] -= "a";
    testing["i"] = "i";

    cout << testing << endl;
}

