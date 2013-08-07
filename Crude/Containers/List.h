#pragma once

/*
	Work of Cremacic

	Creator:	Joshua Richardson (CreMacic Xaio)
	Date:		04/10/2012

	This file is part of the 'Crude Engine' developed by Cremacic, 
*/

#include <assert.h>

namespace Crude {

	/*
		Crude::List

		A dynamic array of Type, this class is used best when you roughly know the size of your content

		NOTE: only use primative types for this class or types with default constructors
	*/

	const static unsigned int DEFAULT_SEGMENT_SIZE = 5;

	template <class Type>
	class List {
	public:
		List( unsigned int Size = DEFAULT_SEGMENT_SIZE );
		List( const Crude::List<Type>& Object );
		~List();
	private:
		unsigned int m_nElements;
		unsigned int m_cMaxElements;
		Type* m_pContainer;
	private:
		void Resize();
	public:
		Type& At( unsigned int Index );
		Type& operator[]( unsigned int Index );
	public:
		Type* Data();
	public:
		bool IsEmpty();
		void Clear();
		unsigned int Size();
		unsigned int MaxSize();
		void Insert( Type const &Object );
		void Remove( unsigned int Index );
		void Swap(unsigned int FirstIndex, unsigned int SecondIndex);
	};

	template <class Type>
	List<Type>::List( unsigned int Size = DEFAULT_SEGMENT_SIZE ) : m_cMaxElements(Size), m_nElements(0) {
		m_pContainer = new Type[m_cMaxElements];
	}

	template <class Type>
	List<Type>::List( const Crude::List<Type>& Object ) {
		this->m_cMaxElements = Object.m_cMaxElements;
		this->m_nElements = Object.m_nElements;
		assert(Object.m_cMaxElements >= Object.m_nElements);
		assert(Object.m_pContainer);
		this->m_pContainer = new Type[Object.m_cMaxElements];
		for (unsigned int i = 0; i < Object.m_nElements; i++) {
			this->m_pContainer[i] = Object.m_pContainer[i];
		}
	}

	template <class Type>
	void List<Type>::Resize() {
		Type* tNewData = new Type[m_nElements + DEFAULT_SEGMENT_SIZE];
		for (unsigned int i = 0; i < m_nElements; i++) {
			tNewData[i] = m_pContainer[i];
		}
		delete[] m_pContainer;
		m_pContainer = tNewData;
		m_cMaxElements = m_nElements + DEFAULT_SEGMENT_SIZE;
	}

	template <class Type>
	Type& List<Type>::At( unsigned int Index ) {
		return m_pContainer[Index];
	}

	template <class Type>
	Type& List<Type>::operator[]( unsigned int Index ) {
		return At(Index);
	}

	template <class Type>
	Type* List<Type>::Data() {
		return m_pContainer;
	}

	template <class Type>
	bool List<Type>::IsEmpty() {
		if (m_nElements == 0)
			return true;
		return false;
	}

	template <class Type>
	void List<Type>::Clear() {
		if (m_nElements != 0) {
			m_nElements = 0;
			m_cMaxElements = 0;
		}
	}

	template <class Type>
	unsigned int List<Type>::Size() {
		return m_nElements;
	}

	template <class Type>
	unsigned int List<Type>::MaxSize() {
		return m_cMaxElements;
	}

	template <class Type>
	void List<Type>::Insert( Type const &Object ) {
		if (m_nElements == m_cMaxElements)
			Resize();
		m_pContainer[m_nElements] = Object;
		m_nElements++;
		return;
	}

	template <class Type>
	void List<Type>::Remove( unsigned int Index ) {
		if (Index > m_nElements-1)
			return;
		for ( unsigned int i = Index; i < m_nElements-1; i++ ) {
			if (i+1 != m_nElements)
				m_pContainer[m_nElements] = m_pContainer[m_nElements+1];
		}
		m_nElements--;
	}

	template <class Type>
	void List<Type>::Swap(unsigned int FirstIndex, unsigned int SecondIndex) {
		if (FirstIndex > m_nElements)
			return;
		if (SecondIndex > m_nElements)
			return;
		Type FirstInstance = m_pContainer[FirstIndex];
		m_pContainer[FirstIndex] = m_pContainer[SecondIndex];
		m_pContainer[SecondIndex] = FirstInstance;
	}

	template <class Type>
	List<Type>::~List() {
		Clear();
		delete[] m_pContainer;
	}

}