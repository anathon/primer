#pragma once

/*
	Work of Cremacic

	Creator:	Joshua Richardson (CreMacic Xaio)
	Date:		04/10/2012

	This file is part of the 'Crude Engine' developed by Cremacic, 
*/

#include "List.h"

namespace Crude {

	template <class Type>
	class Stack {
	public:
		Stack();
		~Stack();
	private:
		Crude::List<Type>* m_pContainer;
	public:
		void Push( Type const &Object );
		Type& Peek();
		Type* Pop();
		bool IsEmpty();
	};

	template <class Type>
	Stack<Type>::Stack() {
		m_pContainer = new Crude::List<Type>();
	}

	template <class Type>
	Stack<Type>::~Stack() {
		delete m_pContainer;
	}

	template <class Type>
	void Stack<Type>::Push( Type const &Object ) {
		m_pContainer->Insert(Object);
	}

	template <class Type>
	Type& Stack<Type>::Peek() {
		return m_pContainer[m_pContainer->Size()-1];
	}

	template <class Type>
	Type* Stack<Type>::Pop() {
		if (m_pContainer->Size() == 0)
			return 0;
		Type* ReturnAddress = &m_pContainer->Data()[m_pContainer->Size()-1];
		m_pContainer->Remove(m_pContainer->Size()-1);
		return ReturnAddress;
		
	}

	template <class Type>
	bool Stack<Type>::IsEmpty() {
		if (m_pContainer->Size() == 0)
			return true;
		return false;
	}
}