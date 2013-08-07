#pragma once

/*
	Work of Cremacic

	Creator:	Joshua Richardson (CreMacic Xaio)
	Date:		04/10/2012

	This file is part of the 'Crude Engine' developed by Cremacic, 
*/

#include "../String/String.h"

namespace Crude {
	
	/*
		Crude::LinkedList

		Double Linked list

	*/

	template <class Type>
	class LinkedList {
	public:
		LinkedList();
		~LinkedList();
	private:
		struct ListNode {
			Type* m_pData;
			ListNode* m_pNext;
			ListNode* m_pPreviouse;
		} *m_EmptyNode;
	private:
		ListNode* m_pHead;
		ListNode* m_pTail;
		ListNode* m_pCurrentNode;
	private:
		unsigned int m_nObjectCount;
	public:
		unsigned int Size();
	public:
		bool IsEmpty();
		void Insert(Type* Object);
		void Remove();
		bool Finished();
		void Slide();
		void SlideFront();
		void Clear();
		Type* Get();
	};

	template <class Type>
	LinkedList<Type>::LinkedList() {
		m_pHead = m_EmptyNode;
		m_pTail = m_EmptyNode;
		m_pCurrentNode = m_EmptyNode;
		m_nObjectCount = 0;
	}

	template <class Type>
	unsigned int LinkedList<Type>::Size() {
		return m_nObjectCount;
	}

	template <class Type>
	bool LinkedList<Type>::IsEmpty() {
		if (m_nObjectCount == 0)
			return true;
		return false;
	}

	template <class Type>
	void LinkedList<Type>::Insert(Type* Object) {

		if (!Object)
			return;

		ListNode* NewObjectWrapper = new ListNode();
		NewObjectWrapper->m_pData = Object;
		NewObjectWrapper->m_pPreviouse = m_pTail;
		NewObjectWrapper->m_pNext = m_EmptyNode;

		if (m_nObjectCount == 0) {
			m_pHead = NewObjectWrapper;
			m_pHead->m_pNext = m_pTail;
			m_pHead->m_pPreviouse = m_EmptyNode;
			m_pCurrentNode = m_pHead;
		} else {
			m_pTail->m_pNext = NewObjectWrapper;
			NewObjectWrapper->m_pPreviouse =  m_pTail;
		}
		m_pTail = NewObjectWrapper;

		m_nObjectCount++;
	}

	template <class Type>
	void LinkedList<Type>::Remove() {
		if (m_pCurrentNode == m_EmptyNode)
			return;

		if(m_nObjectCount == 1) {
			m_pHead = m_EmptyNode;
			m_nObjectCount = 0;
			return;
		}

		if (m_pCurrentNode == m_pHead) {
			m_pHead->m_pNext->m_pPreviouse = m_EmptyNode;
			m_pHead = m_pHead->m_pNext;
			m_pCurrentNode = m_pHead;
			m_nObjectCount--;
			return;
		}

		if (m_pCurrentNode == m_pTail) {
			m_pTail->m_pPreviouse->m_pNext = m_EmptyNode;
			m_pTail = m_pTail->m_pPreviouse;
			m_pCurrentNode = m_pTail;
			m_nObjectCount--;
			return;
		}

		m_pCurrentNode->m_pPreviouse->m_pNext = m_pCurrentNode->m_pNext;
		m_pCurrentNode->m_pNext->m_pPreviouse = m_pCurrentNode->m_pPreviouse;
		m_pCurrentNode = m_pCurrentNode->m_pPreviouse;
		m_nObjectCount--;
	} 

	template <class Type>
	bool LinkedList<Type>::Finished() {
		if (m_pCurrentNode == m_EmptyNode)
			return true;
		return false;
	}

	template <class Type>
	void LinkedList<Type>::Slide() {
		m_pCurrentNode = m_pCurrentNode->m_pNext;
	}

	template <class Type>
	void LinkedList<Type>::SlideFront() {
		m_pCurrentNode = m_pHead;
	}

	template <class Type>
	void LinkedList<Type>::Clear() {
		m_pHead = m_EmptyNode;
		m_pTail = m_EmptyNode;
		m_pCurrentNode = m_EmptyNode;
		m_nObjectCount = 0;
	}

	template <class Type>
	Type* LinkedList<Type>::Get() {
		if (m_nObjectCount != 0)
			return m_pCurrentNode->m_pData;
		return 0;
	}

	template <class Type>
	LinkedList<Type>::~LinkedList() {

	}
}