#ifndef SET_H
#define SET_H

#include <ostream>
#include <cstddef>
#include <cassert>
/**
  @brief classe set

  La classe implementa un set di generici oggetti T.
*/

template <typename T>
class set {

  /**
    @brief struttura element

    struttura dati element interna che viene usata 
    per creare un elemento del set
  */
  struct element {
    T value; ///< valore da memorizzare 
    element *next; ///< puntatore al prossimo elemento del set

    /**
      Costruttore di default

      @post next == nullptr
    */
    element() : next(nullptr) {}

    /**
      Costruttore secondario

      @param v valore da colpiare
      @param n puntatore a next

      @post value == v
      @post next == n
    */
    element(const T &v, element* n) :value(v), next(n) {}

    /**
      Costruttore secondario

      @param v valore da copiare

      @post value == v
      @post next == nullptr
    */
    explicit element(const T &v) : value(v), next(nullptr) {}

    /**
      Costruttore secondario

      @param n puntatore al prossimo element

      @post next == n
    */
    explicit element(element *n) : next(n) {}

    /**
      Copy constructor
      
      Copiamo i dati membro a membro.

      @param other elemento da copiare
    */
    element(const element &other) : value(other.value), next(other.next) {}

    /**
      Operatore di assegnamento. 

      @param other element da copiare

      @return reference all'elemento this
    */
    element &operator=(const element &other) {
      value = other.value;
      next = other.next;
      return *this;
    }

    /**
      Distruttore. 
    */
    ~element() {}
  };

  element *_head;       ///< puntatore al primo element del set
  unsigned int _size;   ///< numero di elementi attuali presenti nel set

public:

  /**
    Costruttore di default.

    @post _head == nullptr
    @post _size == 0
  */
  set() : _head(nullptr), _size(0) {}

  /**
    Copy constructor

    @param other set da copiare

    @post _size = other._size
  */
  set(const set &other) : _head(nullptr), _size(0){
    element *curr = other._head;

    // Cicliamo sugli element di other e mano a mano
    // aggiungiamo un valore dentro this. La add
    // prevede una new e quindi può fallire. Per questo
    // dobbiamo gestire l'evenetuale eccezione che si 
    // genera con un blocco try/catch
    try {
      while (curr != nullptr) {
        add(curr->value);
        curr = curr->next;
      }
    }
    catch(...) {
      // Se c'e' un problema, svuotiamo il set e rilanciamo
      // l'eccezione
      clear();
      throw;
    }
  }

  /**
    Operatore di assegnamento

    @param other set da copiare

    @return reference al set this

    @post _size = other._size
  */
  set &operator=(const set &other) {
    if(this!=&other) {
      set tmp(other);
      std::swap(this->_head, tmp._head);
      std::swap(this->_size, tmp._size);      
    }
    return *this;
  }

  /**
    Distruttore 

    @post _head == nullptr
    @post _size == 0
  */
  ~set() {
    clear();
  }

  /**
    Svuota il set

    @post _head == nullptr
    @post _size == 0
  */
  void clear() {
    element *curr = _head;

    while (curr!=nullptr) {
      element *cnext = curr->next;
      delete curr;
      curr = cnext;
    }
    _size = 0;
    _head = nullptr;
  }

  /**
    Aggiunge un elemento nel set nell'ultima posizione

    @param value valore di tipo T da inserire nel set

    @post _size = _size+1

    @throw std::bad_alloc possibile eccezione di allocazione
  */
 bool add(const T& value) {

    // Caso di set vuoto
    if (_size==0) {
      element *tmp = new element(value);
      _head = tmp;
      _size = 1;
      return true;
    }

    element *curr = _head;
    element *prev = _head;

    // caso in cui il valore value è già presente nel set,
    // quindi non lo si può inserire di nuovo
    while(curr != nullptr) {
      if (curr->value == value)
        return false;
      prev = curr;
      curr = curr->next;
    }

    element *tmp = new element(value);

    // se il valore non era già presente nel set,
    // allora lo inserisco in coda al set
    prev->next = tmp;
    _size++;
    return true;
  }

  /**
    Rimuove dal set l'elemento con valore value, se presente

    @param value valore di tipo T da rimuovere dal set

    @post _size = _size-1
  */
  void remove(const T& value) {
    if(_size == 0)
      return;
    
    element *curr = _head;
    element *prev = _head;

    while(curr != nullptr) {
      if(curr->value == value) {
        if(curr == _head) {
          _head = curr->next;
          delete curr;
          _size--;
          return;
        }
        else {
          prev->next = curr->next;
          delete curr;
          _size--;
          return;
        }
        
      }
      prev = curr;
      curr = curr->next;
    }
  }

  /**
    Ritorna il numero di elementi nel set

    @return il numero di elementi nel set
  */
  unsigned int size() const {
    return _size;
  }

    /**
    Ritorna l'elemento che si trova in posizione pos,
    con accesso in sola lettura

    @return l'i-esimo elemento
  */
  const T &operator[](unsigned int pos) const {
    assert(pos < _size);

    element *curr = _head;
    for(int i = 0; i < pos; ++i)
      curr = curr->next;
    return curr->value;
  }

    /**
    Ritorna true se this e other sono uguali,
    altrimenti false

    @return true/false
  */
  bool operator==(const set &other) const {
    if(_size != other.size()) return false;

    bool trovato = false;

    for(int i = 0; i < _size; ++i) {
      for(int j = 0; j < _size; ++j) {
        if((*this)[i] == other[j]) {
          trovato = true;
          break;
        }
      }
      if(trovato == false) {
        return false;
      }
      trovato = false;
    }
    return true;
  }

  /**
    Costruttore che crea un set riempito con dati
    presi da una sequenza identificata da uniteratore di 
    inizio e uno di fine. Gli iteratori possono essere di
    qualunque tipo. 

    @param b iteratore di inizio sequenza
    @param e iteratore di fine sequenza

    @throw std::bad_alloc possibile eccezione di allocazione
  */
  template <typename MyIter>
  set(MyIter b,  MyIter e) : _head(nullptr), _size(0){
    try {
      for( ; b!=e; ++b)
        add(static_cast<T>(*b)); // la add contiene una new che può fallire
    }
    catch(...) {
      // in caso di errore di memoria si svuota il set
      clear();
      throw;
    }
  }

  /**
  Funzione GLOBALE che implementa l'operatore di stream.
  La funzione è templata sul set ed è messa
  friend perchè accediamo ai dati privati del set.

  @param os stream di output
  @param set set da mandare sullo stream

  @return lo stream di output
  */
  friend std::ostream &operator<<(std::ostream &os, const set<T> &set) {

    element *curr = set._head;
    while(curr !=nullptr) {
      os << curr->value << " ";
      curr = curr->next;
    }

    return os;
  }

  /**
    Gli iteratori devono iterare sui dati inseriti nella classe
    principale. Siccome nel set mettiamo dei dati di 
    tipo T, l'iteratore deve iterare su dati di tipo T.
  */
  class const_iterator {

  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T                         value_type;
    typedef ptrdiff_t                 difference_type;
    typedef const T*                  pointer;
    typedef const T&                  reference;
  
    const_iterator() : ptr(nullptr) {
    }
    
    const_iterator(const const_iterator &other) : ptr(other.ptr) {
    }

    const_iterator& operator=(const const_iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    ~const_iterator() { }

    // Ritorna il dato riferito dall'iteratore (dereferenziamento)
    reference operator*() const {
      return ptr->value;
    }

    // Ritorna il puntatore al dato riferito dall'iteratore
    pointer operator->() const {
      return &(ptr->value);
    }
    
    // Operatore di iterazione post-incremento
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      ptr = ptr->next;
      return tmp;
    }

    // Operatore di iterazione pre-incremento
    const_iterator& operator++() {
      ptr = ptr->next;
      return *this;
    }

    // Uguaglianza
    bool operator==(const const_iterator &other) const {
      return (ptr == other.ptr);
    }
    
    // Diversita'
    bool operator!=(const const_iterator &other) const {
      return (ptr != other.ptr);
    }

  private:
    // La classe container deve essere messa friend dell'iteratore per poter
    // usare il costruttore di inizializzazione.
    friend class set; 

    // Costruttore privato di inizializzazione usato dalla classe container
    // tipicamente nei metodi begin e end
    const_iterator(const element *p) : ptr(p) { }
    
    const element * ptr;
    
  }; // classe const_iterator
  
  // Ritorna l'iteratore all'inizio della sequenza dati
  const_iterator begin() const {
    return const_iterator(_head);
  }
  
  // Ritorna l'iteratore alla fine della sequenza dati
  const_iterator end() const {
    return const_iterator(nullptr);
  }

}; // fine set

/**
  Funzione GLOBALE che implementa l'operatore di concatenazione.
  La funzione è templata sul set.

  @param s1 primo set
  @param s2 secondo set

  @return il nuovo set
*/
template <typename T>
set<T> operator+(const set<T> &s1, const set<T> &s2) {

  bool trovato = false;

  set<T> tmp(s1);

  if(s1 == s2)
    return tmp;

  try{
    for(typename set<T>::const_iterator b2 = s2.begin(); b2 != s2.end(); ++b2) {
      for(typename set<T>::const_iterator b1 = s1.begin(); b1 != s1.end(); ++b1) {
        if(*b2 == *b1)
          trovato = true;
      }
      if(trovato == false)
        tmp.add(*b2);
      trovato = false;
    }
  }
  catch(...) {
    tmp.clear();
    throw;
  }

  return tmp;
}

/**
  Funzione GLOBALE che implementa l'operatore di intersezione.
  La funzione è templata sul set.

  @param s1 primo set
  @param s2 secondo set

  @return il nuovo set
*/
template <typename T>
set<T> operator-(const set<T> &s1, const set<T> &s2) {

  bool trovato = false;

  if(s1 == s2) {
    set <T> tmp = set<T>(s1);
    return tmp;
  }

  set<T> tmp = set<T>();

  try {
    for(typename set<T>::const_iterator b1 = s1.begin(); b1 != s1.end(); ++b1) {
      for(typename set<T>::const_iterator b2 = s2.begin(); b2 != s2.end(); ++b2) {
        if(*b1 == *b2)
          tmp.add(*b1);
      }
    }
  }
  catch(...) {
    tmp.clear();
    throw;
  }

  return tmp;
}

/**
  funzione globale e generica filter_out che, dato un
  Set generico S su tipi T e un predicato booleano generico P, ritorna un 
  nuovo set di tipi T ottenuto prendendo da S tutti gli elementi che soddisfano 
  il predicato P.

  @param s1 set da analizzare
  @param pred predicato

  @return il nuovo set con solo gi elementi che soddisfano il predicato 
*/
template <typename T, typename P>
set<T> filter_out(const set<T> &s1, P pred) {
  typename set<T>::const_iterator b, e;

  set<T> tmp;

  try {
    for(b = s1.begin(), e = s1.end(); b!=e; ++b) {
      if (pred(*b))
      tmp.add(*b);
    }
  }
  catch(...) {
    tmp.clear();
    throw;
  }

  return tmp;
}

#endif