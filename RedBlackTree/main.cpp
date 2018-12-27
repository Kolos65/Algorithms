#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include "rb_tree.hpp"

using namespace std;

int main()
{
    srand(time(0));

    try {
        {
            cout << "\n_rebalance_after_insert, 1. eset\n" << endl;
            rb_tree<int> bal, jobb;
            vector<int> elemek = {10, 5, 11, 1, 7, 0};
            for (int e : elemek) {
                bal.insert(e);
                jobb.insert(-e);
            }
            bal.validate();
            jobb.validate();
        }
        {
            cout << "\n_rebalance_after_insert, 3. eset\n" << endl;
            rb_tree<int> bal, jobb;
            vector<int> elemek = {10, 12, 5, 1, 2, 0};
            for (int e : elemek) {
                bal.insert(e);
                jobb.insert(-e);
            }
            bal.validate();
            jobb.validate();
        }
        {
            cout << "\n_rebalance_after_insert, 2. eset\n" << endl;
            rb_tree<int> bal, jobb;
            vector<int> elemek = {10, 12, 5, 1, 2, 4};
            for (int e : elemek) {
                bal.insert(e);
                jobb.insert(-e);
            }
            bal.validate();
            jobb.validate();
        }
        {
            cout << "\n_rebalance_after_remove, 4. eset\n" << endl;
            rb_tree<int> bal, jobb;
            vector<int> elemek = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            for (int e : elemek) {
                bal.insert(e);
                jobb.insert(-e);
            }
            bal.remove(7);
            jobb.remove(-7);
            bal.validate();
            jobb.validate();
        }
        {
            cout << "\n_rebalance_after_remove, 3. eset\n" << endl;
            rb_tree<int> bal, jobb;
            vector<int> elemek = {1, 2, 3, 4, 5, 6, 7, 8, 10, 9};
            for (int e : elemek) {
                bal.insert(e);
                jobb.insert(-e);
            }
            bal.remove(7);
            jobb.remove(-7);
            bal.validate();
            jobb.validate();
        }
        {
            cout << "\n_rebalance_after_remove, 1. eset\n" << endl;
            rb_tree<int> bal, jobb;
            vector<int> elemek = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            for (int e : elemek) {
                bal.insert(e);
                jobb.insert(-e);
            }
            bal.remove(5);
            jobb.remove(-5);
            bal.validate();
            jobb.validate();
        }
        /*
         *       Futtatunk egy tesztet, amely 1000 véletlen számot szúr be a piros-fekete fánkba.
         *       Minden egyes beszúrás után ellenőrizzük, hogy az adatszerkezet érvényes piros-fekete fa-e.
         *
         *       Hogy kizárjuk annak lehetőségét, hogy véletlenül csúcsokat drótozunk ki a fából,
         *       amikor nem is akarunk törölni, ugyanezeket a számokat beszúrjuk egy std::set-be is,
         *       majd ellenőrizzük, hogy a két adatszerkezet ugyanannyi elemet tartalmaz-e.
         *
         *       Végül az std::set-ből az elemeket kimásoljuk egy std::vector-ba, amit megkeverünk,
         *       hogy véletlenszerű sorrendben tudjuk törölni az összes elemet a fából.
         *       Ezzel ellenőrizzük, hogy a törlés jól működik-e, és a végén megnézzük, hogy tényleg
         *       üres lett-e a piros-fekete fánk.
        */

        cout << "\n*** Kis elemszamu, reszletes teszt futtatasa ***\n" << endl;

        set<int> stdShort;
        rb_tree<int> myShort;
        for (int i=0; i<1000; i++) {
            if (i%100 == 0)
                cout << i+100 << " elem beszurasa...";

            int x = rand();
            stdShort.insert(x);
            myShort.insert(x);
            myShort.validate();

            if ((i+1)%100 == 0)
                cout << " ok." << endl;
        }

        if (myShort.size() != stdShort.size())
            throw internal_error("Meret nem egyezik!");
        cout << "\nMeret rendben.\n" << endl;

        vector<int> arrayShort(stdShort.begin(), stdShort.end());
        random_shuffle(arrayShort.begin(), arrayShort.end());

        for (size_t i=0; i<arrayShort.size(); i++) {
            if (i%100 == 0)
                cout << i+100 << " elem torlese...";

            myShort.remove(arrayShort[i]);
            myShort.validate();

            if ((i+1)%100 == 0 || i+1==arrayShort.size())
                cout << " ok." << endl;
        }
        if (myShort.size() != 0)
            throw internal_error("Meret nem egyezik!");
        cout << "\nMeret rendben.\n" << endl;

        /*
         * Most egymillió véletlen számot szúrunk be a piros-fekete fába, és párhuzamosan egy
         * std::set-be. Csak a végén ellenőrizzük, hogy érvényes-e az piros-fekete fa és egyezik-e a két adatszerkezet mérete.
         *
         * Ezután megnézzük, hogy minden std::set-beli elem megtalálható-e a piros-fekete fában,
         * majd sorban kitöröljuk őket, és ellenőrizzük, hogy üres lett-e a fa.
         *
         * Ennek a tesztnek néhány másodperc alatt le kell futnia. Ha fél percnél tovább
         * tart, akkor olyan hiba lehet a kódban, ami elrontja az aszimptotikus futási időt.
        */

        cout << "\n*** Nagy elemszamu teszt futtatasa ***\n" << endl;

        cout << "Beszuras...";
        set<int> stdLong;
        rb_tree<int> myLong;
        for (int i=0; i<1000000; i++) {
            int x = rand();
            stdLong.insert(x);
            myLong.insert(x);
        }

        myLong.validate();
        if (myLong.size() != stdLong.size())
            throw internal_error("Meret nem egyezik!");
        cout << " ok." << endl;

        cout << "Torles...";
        for (set<int>::iterator it = stdLong.begin(); it != stdLong.end(); it++)
            if (!myLong.find(*it))
                throw internal_error("Elem veszett el a fabol!");

        for (set<int>::iterator it = stdLong.begin(); it != stdLong.end(); it++)
            myLong.remove(*it);

        myLong.validate();
        if (myLong.size() != 0)
            throw internal_error("Meret nem egyezik!");
        cout << " ok." << endl;
    }
    catch (const exception& e) {
        cout << "HIBA: " << e.what() << endl;
    }

    return 0;
}
