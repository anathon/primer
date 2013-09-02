#pragma once

/*
	Work of Cremacic

	Creator:	Joshua Richardson (CreMacic Xaio)
	Date:		04/10/2012

	This file is part of the 'Crude Engine' developed by Cremacic, 
*/

#include "LinkedList.h"

namespace Crude {

	/*
		Crude::Que

		A que container, simple FIFO architecture.

	*/

	template <class Type>
	class Que {
	public:
		Que();
		Que(const Que& Object );
		~Que();
	public:
		Crude::LinkedList<Type> m_pData;
	public:
		void			Push(Type* Object);
		Type*			Peek();
		Type*			Pop();
		unsigned int	Size();
	};

	template <class Type>
	Que<Type>::Que() {
	}

	template <class Type>
	Que<Type>::Que(const Que &Object ){
	}

	template <class Type>
	Que<Type>::~Que(){
	}

	template <class Type>
	void Que<Type>::Push(Type* Object) {
		m_pData.Insert(Object);
	}

	template <class Type>
	Type* Que<Type>::Peek() {
		m_pData.SlideFront();
		return m_pData.Get();
	}

	template <class Type>
	Type* Que<Type>::Pop() {
		m_pData.SlideFront();
		Type* ReturnAddress = m_pData.Get();
		m_pData.Remove();
		return ReturnAddress;
	}

	template <class Type>
	unsigned int Que<Type>::Size() {
		return m_pData.Size();
	}

}