//
// Created by alejandro on 21/03/25.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H


template <typename T>
class DoublyLinkedList {
private:
	class Nodo{
	private:
		T _dato;
    	Nodo* _siguiente;
    	Nodo* _anterior;
        Nodo() : _dato(T()), _siguiente(nullptr), _anterior(nullptr) {};
    	Nodo(const T& dato, Nodo* siguiente = nullptr, Nodo* anterior = nullptr) :
    	  _dato(dato), _siguiente(siguiente), _anterior(anterior) {};

        friend class DoublyLinkedList;

    public:
        ~Nodo() {};
    	const T& operator*() const {return _dato;}
    	T& operator*() {return _dato;}
        bool null() const {return _dato == T();}
    };

    Nodo* _primero;
    Nodo* _ultimo;
    Nodo* _actual;
    int _size;

    // O(n)

    void setDefault(){
        while(!_primero->_siguiente->null()){
            Nodo* aux = this->_primero;
            this->_primero->_anterior = nullptr;
            this->_primero->_siguiente = nullptr;
            this->_primero = aux->_siguiente;
            this->_size--;
        }
    }

public:

  	// Constructores

  	DoublyLinkedList() : _primero(nullptr), _ultimo(nullptr), _actual(nullptr), _size(0) {};

    DoublyLinkedList(const DoublyLinkedList& otro){
    	if(this != &otro){*this = otro;}
    }

    // O(n)

    DoublyLinkedList& operator=(const DoublyLinkedList& otro){
    	if(this == &otro){return *this;}
        else {
          	this->setDefault();
        	for(int i = 0; i < otro.size(); i++)
                  this->push_back(otro.at(i));

            return *this;
        }
    }

    // Información sobre la estructura (O(1))

    int size() const {return _size;}
    bool empty() const {return this->size() == 0;}

    // Manipulación y acceso a datos (O(1))

    const T& front() const {
	    if (_primero)
	    	return this->_primero->_dato;
    	else
    		throw std::out_of_range("No hay elementos en la lista");
    }
    const T& back() const {
	    if (_ultimo)
	    	return this->_ultimo->_dato;
    	else
    		throw std::out_of_range("No hay elementos en la lista");
    }
    T& front() {
	    if (_primero)
	    	return this->_primero->_dato;
    	else
    		throw std::out_of_range("No hay elementos en la lista");
    }
    T& back() {
	    if (_ultimo)
	    	return this->_ultimo->_dato;
    	else
    		throw std::out_of_range("No hay elementos en la lista");
    }

    void push_back(const T& dato){

    	if (this->empty()) {
    		this->_primero = new Nodo(dato);
    		this->_ultimo = this->_primero;
    		this->_size++;
    	}
    	else if (this->size() == 1) {
    		this->_ultimo = new Nodo(dato, nullptr, this->_primero);
    		this->_primero->_siguiente = this->_ultimo;
    		this->_size++;
    	}
    	else {
    		Nodo* aux = this->_ultimo;
    		this->_ultimo = new Nodo(dato, nullptr, aux);
    		this->_ultimo->_anterior = aux;
    		this->_ultimo->_anterior->_siguiente = this->_ultimo;
    		this->_size++;
    	}
    }
    void push_front(const T& dato){
      	if (this->empty()) {
      		this->_primero = new Nodo(dato);
      		this->_ultimo = this->_primero;
      		this->_size++;
      	} else if (this->size() == 1) {
      		this->_primero = new Nodo(dato, this->_ultimo, nullptr);
      		this->_ultimo->_anterior = this->_primero;
      		this->_size++;
      	} else {
      		Nodo* aux = this->_primero;
      		this->_primero = new Nodo(dato, aux, nullptr);
      		this->_primero->_siguiente = aux;
      		this->_primero->_siguiente->_anterior = this->_primero;
      		this->_size++;
      	}
    }
    void pop_back(){
    	if (!this->empty()) {
    		Nodo* aux = this->_ultimo;
    		this->_ultimo = this->_ultimo->_anterior;
    		this->_ultimo->_siguiente = nullptr;
    		delete aux;
    		this->_size--;
    	}
    }
    void pop_front(){
    	if (!this->empty()) {
    		Nodo* aux = this->_primero;
    		this->_primero = this->_primero->_siguiente;
    		this->_primero->_anterior = nullptr;
    		delete aux;
    		this->_size--;
    	}
    }

    // Acceso arbitrario (O(n))

	const T& at(int pos) const {
    	if(pos == 0) return this->front();
    	if(pos == this->size() - 1) return this->back();
    	else if(!(pos < 0 || pos >= this->size())){
    		Nodo* aux = this->_primero;
    		for(int i = 0; i < pos; i++)
    			aux = aux->_siguiente;
    		return (*aux);
    	}
    }

	T& at(int pos) {
    	if(pos == 0) return this->front();
    	if(pos == this->size() - 1) return this->back();
    	else if(!(pos < 0 || pos >= this->size())){
    		Nodo* aux = this->_primero;
    		for(int i = 0; i < pos; i++)
    			aux = aux->_siguiente;
    		return (*aux);
    	}
    }

    const T& operator[](int pos) const {return this->at(pos);}
    T& operator[](int pos) {return this->at(pos);}

    void insert(int pos, const T& dato){
    	if(pos == 0) this->push_front(dato);
        if(pos == this->size()) this->push_back(dato);
        else if(!(pos < 0 || pos > this->size())){
          	Nodo* aux = this->_primero;
            for(int i = 0; i < pos; i++){
                if(i > this->size() - 1) this->push_back(T());
                aux = aux->_siguiente;
            }
            Nodo* nuevo = new Nodo(dato, aux, aux->_anterior);
            aux->_anterior->_siguiente = nuevo;
            aux->_anterior = nuevo;
        }
    }

    // Búsqueda (O(n))

    int find(const T& dato) const {
      	Nodo* principio = this->_primero;
        int pos = -1;
        int curr = 0;
        while(principio != nullptr){
          	if((*principio) == dato) return curr;
            curr++;
            principio = principio->_siguiente;
        }
    }

    // "Métodos de iteradortes" (O(1))

    const T& begin() const {this->_actual = this->_primero; return this->front();}
    const T& end() const {this->_actual = nullptr; return this->back();}
    const T& next() const {this->_actual = this->_actual->_siguiente; return this->_actual->_siguiente->_dato;}
    const T& prev() const {this->_actual = this->_actual->_anterior; return this->_actual->_anterior->_dato;}
    T& begin() {this->_actual = this->_primero; return this->front();}
    T& end() {this->_actual = nullptr; return this->back();}
    T& next() {this->_actual = this->_actual->_siguiente; return this->_actual->_siguiente->_dato;}
    T& prev() {this->_actual = this->_actual->_anterior; return this->_actual->_anterior->_dato;}

    // Posición de puntero current (O(n))

    int whereAmI() const {return this->find(this->_actual);}


};



#endif //DOUBLYLINKEDLIST_H
