#include <iostream>
#include "set.h"

void test_int() {

    bool res = false;

    std::cout << std::endl;
    std::cout << "di seguito verranno eseguiti i test sul tipo int" << std::endl;
    std::cout << std::endl;

    //creo il predicato, ritorna true se il valore in input è pari
    struct is_even {
        bool operator()(int a) const {
            return (a%2 == 0);
        }
    };

    //creo un'istanza del predicato
    is_even ie;

    //testo il costruttore di default
    set<int> s1 = set<int>();

    //testo la size su un set vuoto
    std::cout << "size s1: " << s1.size() << std::endl;

    //testo la add provando anche ad aggiungere elementi con lo stesso valore
    res = s1.add(10);
    s1.add(10);
    s1.add(20);
    s1.add(30);
    s1.add(26);
    s1.add(25);
    s1.add(27);
    s1.add(28);
    s1.add(29);
    s1.add(29);
    s1.add(29);
    s1.add(28);

    //testo operatore <<
    std::cout << "s1: " << s1 << std::endl;

    //testo la size su un set con alcuni elementi
    std::cout << "size s1: " << s1.size() << std::endl;

    //testo il copy constructor
    set<int> s2(s1);

    //testo operatore <<
    std::cout << "s2: " << s2 << std::endl;

    //testo l'operatore di assegnamento
    set<int> s3;
    s3 = s1;

    //testo operatore <<
    std::cout << "s3: " << s3 << std::endl;

    //testo la clear
    s1.clear();

    //testo operatore <<
    std::cout << "s1: " << s1 << std::endl;

    //testo la size su un set che è stato riempito e poi svuotato
    std::cout << "size s1: " << s1.size() << std::endl;

    //testo la remove
    s2.remove(25);

    //testo operatore <<
    std::cout << "s2: " << s2 << std::endl;

    //testo operatore []
    std::cout << "s2[3]: " << s2[3] << std::endl;

    //testo operatore []
    std::cout << "s3[4]: " << s3[4] << std::endl;

    //testo operatore == su due set uguali
    set<int> s4 = set<int>();
    s4.add(1);
    s4.add(2);
    s4.add(3);
    s4.add(4);

    set<int> s5 = set<int>();
    s5.add(4);
    s5.add(3);
    s5.add(2);
    s5.add(1);

    std::cout <<"s4==s5 (true): " << (s4==s5) << std::endl;

    //testo operatore == su due set diversi
    s5.remove(4);
    s5.add(7);
    
    std::cout <<"s4==s5 (false): " << (s4==s5) << std::endl;

    //testo il costruttore con due iteratore in input
    set<int> s6 = set<int>();
    s6.add(40);
    s6.add(80);
    s6.add(70);
    s6.add(90);

    std::cout << "s6: " << s6 << std::endl;

    set<int> s7 = set<int>(s6.begin(), s6.end());

    std::cout << "s7: " << s7 << std::endl;

    //testo la stampa tramite l'iteratore
    std::cout << "s7: ";
    for(set<int>::const_iterator b = s7.begin(); b != s7.end(); ++b)
        std::cout << *b << " ";
    std::cout << std::endl;

    //testo operator +
    set<int> s8;
    s8.add(15);
    s8.add(0);
    s8.add(20);
    s8.add(30);

    set<int> s9;
    s9.add(0);
    s9.add(10);
    s9.add(25);
    s9.add(15);
    s9.add(35);

    std::cout << "s8: " << s8 << std::endl;
    std::cout << "s9: " << s9 << std::endl;

    set<int> s10;

    s10 = (s8+s9);

    std::cout << "s8 + s9: " << s10 << std::endl;

    //testo operator -
    set<int> s11(s8-s9);

    std::cout << "s8 - s9: " << s11 << std::endl;

    //testo la funzione filter out su un set che contiene alcuni
    //valori che soddisfano il predicato, passando in input un predicato
    //che richiede che l'elemento analizzato sia pari
    s10 = filter_out(s10, ie);

    std::cout << "filter_out(s10): " << s10 << std::endl;

    std::cout << "size s10: " << s10.size() << std::endl;

    //testo la funzione filter out su un set che non contiene
    //valori che soddisfano il predicato, passando in input un predicato
    //che richiede che l'elemento analizzato sia pari
    set<int> s12 = set<int>();

    s12.add(1);
    s12.add(5);
    s12.add(55);
    s12.add(59);
    s12.add(65);
    s12.add(71);

    std::cout << "s12: " << s12 << std::endl;

    set<int>s13 = set<int>(filter_out(s12, ie));

    std::cout << "filter_out(s13): " << s13 << std::endl;

    std::cout << "size s13: " << s13.size() << std::endl;

    //testo la funzione filter_out su un set vuoto
    set<int> s14 = set<int>();

    set<int> s15 = set<int>(filter_out(s14, ie));

    std::cout << "s15: " << s15 << std::endl;
    
    std::cout << "size s15: " << s15.size() << std::endl;
    return;
}

void test_char() {

    std::cout << std::endl;
    std::cout << "di seguito verranno eseguiti i test sul tipo char" << std::endl;
    std::cout << std::endl;
    
    //creo il predicato, ritorna true se il carattere passato è uguale al carattere 'c'
    struct is_good {
        bool operator()(char a) const {
            return (a == 'c');
        }
    };

    //creo un'istanza del predicato
    is_good ig;

    //testo il costruttore di default
    set<char> s1 = set<char>();

    //testo la size su un set vuoto
    std::cout << "size s1: " << s1.size() << std::endl;

    //testo la add provando anche ad aggiungere elementi con lo stesso valore
    s1.add('a');
    s1.add('b');
    s1.add('c');
    s1.add('f');
    s1.add('a');
    s1.add('b');
    s1.add('c');
    s1.add('d');
    s1.add('h');
    s1.add('z');
    s1.add('e');
    s1.add('f');

    //testo operatore <<
    std::cout << "s1: " << s1 << std::endl;

    //testo la size su un set con alcuni elementi
    std::cout << "size s1: " << s1.size() << std::endl;

    //testo il copy constructor
    set<char> s2(s1);

    //testo operatore <<
    std::cout << "s2: " << s2 << std::endl;


    //testo l'operatore di assegnamento
    set<char> s3;
    s3 = s1;

    //testo operatore <<
    std::cout << "s3: " << s3 << std::endl;

    //testo la clear
    s1.clear();

    //testo operatore <<
    std::cout << "s1: " << s1 << std::endl;

    //testo la size su un set che è stato riempito e poi svuotato
    std::cout << "size s1: " << s1.size() << std::endl;

    //testo la remove
    s2.remove('b');

    //testo operatore <<
    std::cout << "s2: " << s2 << std::endl;

    //testo operatore []
    std::cout << "s2[3]: " << s2[3] << std::endl;

    //testo operatore []
    std::cout << "s3[4]: " << s3[4] << std::endl;

    //testo operatore == su due set uguali
    set<char> s4 = set<char>();
    s4.add('h');
    s4.add('z');
    s4.add('e');
    s4.add('f');

    set<char> s5 = set<char>();
    s5.add('h');
    s5.add('z');
    s5.add('e');
    s5.add('f');

    std::cout <<"s4==s5 (true): " << (s4==s5) << std::endl;

    //testo operatore == su due set diversi
    s5.remove('e');
    s5.add('a');
    
    std::cout <<"s4==s5 (false): " << (s4==s5) << std::endl;

    //testo il costruttore con due iteratore in input
    set<char> s6 = set<char>();
    s6.add('g');
    s6.add('s');
    s6.add('h');
    s6.add('f');

    std::cout << "s6: " << s6 << std::endl;

    set<char> s7 = set<char>(s6.begin(), s6.end());

    std::cout << "s7: " << s7 << std::endl;

    //testo la stampa tramite l'iteratore
    std::cout << "s7: ";
    for(set<char>::const_iterator b = s7.begin(); b != s7.end(); ++b)
        std::cout << *b << " ";
    std::cout << std::endl;

    //testo operator +
    set<char> s8;
    s8.add('a');
    s8.add('b');
    s8.add('c');
    s8.add('d');

    set<char> s9;
    s9.add('e');
    s9.add('d');
    s9.add('a');
    s9.add('c');
    s9.add('f');

    std::cout << "s8: " << s8 << std::endl;
    std::cout << "s9: " << s9 << std::endl;

    set<char> s10 = set<char>();

    s10 = (s8+s9);

    std::cout << "s8 + s9: " << s10 << std::endl;

    //testo operator -
    set<char> s11(s8-s9);

    std::cout << "s8 - s9: " << s11 << std::endl;

    //testo la funzione filter out su un set che contiene
    //alcuni valori che soddisfano il predicato, passando in input un predicato
    //che richiede che l'elemento analizzato sia uguale al carattere 'c'
    s10 = filter_out(s10, ig);

    std::cout << "filter_out(s10): " << s10 << std::endl;

    std::cout << "size s10: " << s10.size() << std::endl;

    //testo la funzione filter out su un set che non contiene
    //valori che soddisfano il predicato, passando in input un predicato
    //che richiede che l'elemento analizzato sia uguale al carattere 'c'
    set<char> s12 = set<char>();
    s12.add('e');
    s12.add('d');
    s12.add('a');
    s12.add('f');

    set<char> s13 = set<char>(filter_out(s12, ig));
    std::cout << "s13: " << s13 << std::endl;
    std::cout << "size s13: " << s13.size() << std::endl;
    return;
}

//costruisco un dato custom "point" tramite una struct
struct point {
    int x; ///< coordinata x del punto
   int y; ///< coordinata y del punto

    point(int xx, int yy) : x(xx), y(yy) {}
};

std::ostream &operator<<(std::ostream &os, const point &p) {
    std::cout<<"("<<p.x<<","<<p.y<<")";
        return os;
}

bool operator==(const point &p1, const point &p2) {
  return ((p1.x == p2.x) && (p1.y == p2.y));
}

void test_point() {

    std::cout << std::endl;
    std::cout << "di seguito verranno eseguiti i test sul tipo custom \"point\" " << std::endl;
    std::cout << std::endl;

    //creo il predicato, ritorna true se la coordinata x del punto è <= 10
    struct is_good {
        bool operator()(point a) const {
            return (a.x <= 10);
        }
    };

    //creo un'istanza del predicato
    is_good ig;

    //testo il costruttore di default
    set<point> s1;

    //testo operatore <<
    std::cout << "s1: " << s1 << std::endl;

    //testo la size su un set vuoto
    std::cout << "size s1: " << s1.size() << std::endl;
    
    //testo la add provando anche ad aggiungere elementi con lo stesso valore
    s1.add(point(1,1));
    s1.add(point(1,2));
    s1.add(point(2,7));
    s1.add(point(1,1));
    s1.add(point(0,0));
    s1.add(point(5,4));;

    //testo operatore <<
    std::cout << "s1: " << s1 << std::endl;

    //testo la size
    std::cout << "size s1: " << s1.size() << std::endl;

    //testo il copy constructor
    set<point> s2(s1);

    //testo operatore <<
    std::cout << "s2: " << s2 << std::endl;

    //testo l'operatore di assegnamento
    set<point> s3;
    s3 = s1;

    std::cout << "s3: " << s3 << std::endl;

    //testo la clear
    s1.clear();

    //testo operatore <<
    std::cout << "s1: " << s1 << std::endl;

    //testo la size su un set che è stato riempito e poi svuotato
    std::cout << "size s1: " << s1.size() << std::endl;

    //testo operatore <<
    std::cout << "s2: " << s2 << std::endl;

    //testo la remove
    std::cout << "tolgo (2,7) da s2" << std::endl;
    s2.remove(point(2,7));

    //testo operatore <<
    std::cout << "s2: " << s2 << std::endl;

    //testo operatore []
    std::cout << "s2[0]: " << s2[0] << std::endl;

    //testo operatore []
    std::cout << "s2[3]: " << s2[3] << std::endl;

    //testo operatore == su due set uguali
    set<point> s4 = set<point>();
    s4.add(point(5,7));
    s4.add(point(7,5));
    s4.add(point(45,22));
    s4.add(point(7,12));

    set<point> s5 = set<point>();
    s5.add(point(45,22));
    s5.add(point(5,7));
    s5.add(point(7,12));
    s5.add(point(7,5));

    std::cout <<"s4==s5 (true): " << (s4==s5) << std::endl;

    //testo operatore == su due set diversi
    s5.remove(point(45,22));
    s5.add(point(500,400));
    
    std::cout <<"s4==s5 (false): " << (s4==s5) << std::endl;

    //testo il costruttore con due iteratore in input
    set<point> s6;
    s6.add(point(45,22));
    s6.add(point(50,70));
    s6.add(point(77,122));
    s6.add(point(71,52));

    std::cout << "stampa tramite operatore<< di s6: " << s6 << std::endl;

    set<point> s7 = set<point>(s6.begin(), s6.end());

    std::cout << "stampa tramite operatore<< di s7: " << s7 << std::endl;

    //testo la stampa tramite l'iteratore
    std::cout << "stampa tramite iteratore di s7: ";
    for(set<point>::const_iterator b = s7.begin(); b != s7.end(); ++b)
        std::cout << *b << " ";
    std::cout << std::endl;

    //testo operator +
    set<point> s8;
    s8.add(point(45,22));
    s8.add(point(50,70));
    s8.add(point(77,122));
    s8.add(point(71,52));

    set<point> s9;
    s9.add(point(45,25));
    s9.add(point(50,79));
    s9.add(point(77,132));
    s9.add(point(71,52));

    std::cout << "s8: " << s8 << std::endl;
    std::cout << "s9: " << s9 << std::endl;

    set<point> s10 = set<point>(s8+s9);

    std::cout << "s8 + s9: " << s10 << std::endl;

    //testo operator -
    set<point> s11(s8-s9);

    std::cout << "s8 - s9: " << s11 << std::endl;
    
    //testo la funzione filter out su un set che contiene
    //alcuni valori che soddisfano il predicato, passando in input un predicato
    //che richiede che il punto analizzato abbia la coordinata x <= 10
    s10.clear();
    
    s10.add(point(45,25));
    s10.add(point(50,79));
    s10.add(point(77,132));
    s10.add(point(7,12));
    s10.add(point(71,52));
    s10.add(point(10,12));

    std::cout << "s10: " << s10 << std::endl;

    s10 = filter_out(s10, ig);

    std::cout << "filter_out(s10): " << s10 << std::endl;

    std::cout << "size s10: " << s10.size() << std::endl;

    //testo la funzione filter out su un set che non contiene
    //valori che soddisfano il predicato, passando in input un predicato
    //che richiede che il punto analizzato abbia la coordinata x <= 10
    set<point> s12 = set<point>();
    s12.add(point(45,25));
    s12.add(point(50,79));
    s12.add(point(77,132));
    s12.add(point(71,52));

    std::cout << "s12: " << s12 << std::endl;

    set<point> s13 = set<point>(filter_out(s12, ig));

    std::cout << "filter_out(s12): " << s13 << std::endl;

    std::cout << "size s13: " << s13.size() << std::endl;
    return;
}

int main() {
    //testo le tre funzioni
    test_int();
    test_char();
    test_point();
}