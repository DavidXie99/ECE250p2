#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  d34xie
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	delete[] array;
	delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
	return array_size;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
	return count == 0;
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	int k = static_cast<int>(obj);
	k = k % array_size;
	if (k < 0){
		k = k + array_size;
	}
	return k;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	int k = static_cast<int>(obj);
	k = k / array_size;
	k = k % array_size;
	if (k < 0){
		k = k + array_size;
	}
	if ( !(k%2)){
		k++;
	}
	return k;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	int probe = h1(obj);
	int offset = h2(obj);
	while (array_state[probe] != EMPTY){
		probe = (probe + offset)%array_size;
		if (array_state[probe] == OCCUPIED && array[probe] == obj){
			return true;
		}
	}
	return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
	return array[n];
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	if (count == array_size){
		throw overflow();
	}
	int probe = h1(obj);
	int offset = h2(obj);
	while (array_state[probe] == OCCUPIED){
		probe = (probe + offset)%array_size;
	}
	array[probe] = obj;
	array_state[probe] = OCCUPIED;
	count++;
	return ; 
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	int probe = h1(obj);
	int offset = h2(obj);
	while (array_state[probe] != EMPTY){
		probe = (probe + offset)%array_size;
		if (array_state[probe] == OCCUPIED && array[probe] == obj){
			array_state[probe] = DELETED;
			count--;
			return true;
		}
	}
	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
	delete[] array;
	delete[] array_state;
	
	count = 0;
	array = new T[array_size];
	array_state = new state[array_size];
	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
	return ; 
}

//Print function won't be tested
template<typename T >
void DoubleHashTable<T >::print() const {
      // enter your implemetation here 	
	return;
}

#endif
