#pragma once

/*
	Work of Cremacic

	Creator:	Joshua Richardson (CreMacic Xaio)
	Date:		04/10/2012

	This file is part of the 'Crude Engine' developed by Cremacic, 
*/

#include "List.h"
#include "LinkedList.h"

namespace Crude {

	/*
		Crude::Hashmap

		Hash map container optimised for long runtime creation but quick retrival.
	*/

	template <class Type>
	class HashMap {
	public:
		HashMap(unsigned int BaseSize);
		~HashMap();
	private:
		unsigned int m_nSize;
		unsigned int m_nElements;
	private:
		struct HashNode {
			unsigned __int64 Key;
			Type* Data;
		};
		Crude::List<Crude::LinkedList<HashNode>>* m_pData;
	public:
		bool IsEmpty();
		void Insert(Crude::String Key, Type* Data);
		void Remove(Crude::String Key);
		Type* Get(Crude::String Key);
	};

	template <class Type>
	HashMap<Type>::HashMap(unsigned int BaseSize) {
		m_pData = new Crude::List<Crude::LinkedList<HashNode>>(BaseSize);
		m_nSize = BaseSize;
		m_nElements = 0;
	}

	template <class Type>
	bool HashMap<Type>::IsEmpty() {
		if (m_nElements == 0)
			return true;
		return false;
	}

	template <class Type>
	void HashMap<Type>::Insert(Crude::String Key, Type* Data) {

		if (!Data)
			return;

		Type* Item = Get(Key);
		if (Item != 0) {
			*Item = *Data;
			return;
		}

		HashNode* Object = new HashNode();
		Object->Key = Key.Hash();
		Object->Data = Data;
		m_pData->At(Key.Hash()%m_nSize).Insert(Object);
		m_nElements++;
	}

	template <class Type>
	void HashMap<Type>::Remove(Crude::String Key) {

		if (m_nElements == 0)
			return;

		unsigned __int32 HashIndex = Key.Hash()%m_nSize;
		unsigned __int64 KeyHash = Key.Hash();

		if (m_pData->At(HashIndex).Size() == 0)
			return;

		m_pData->At(HashIndex).SlideFront();
		while (!m_pData->At(HashIndex).Finished()) {
			HashNode* TargetKey = m_pData->At(HashIndex).Get();
			if (TargetKey->Key == KeyHash) {
				m_pData->At(HashIndex).Remove();
				break;
			}
			m_pData->At(HashIndex).Slide();
		}

		m_nElements--;
	}

	template <class Type>
	Type* HashMap<Type>::Get(Crude::String Key) {
		if (m_nElements == 0)
			return 0;

		unsigned __int32 HashIndex = Key.Hash()%m_nSize;
		unsigned __int64 KeyHash = Key.Hash();

		if (m_pData->At(HashIndex).Size() == 0)
			return 0;

		m_pData->At(HashIndex).SlideFront();
		while (!m_pData->At(HashIndex).Finished()) {
			HashNode* TargetKey = m_pData->At(HashIndex).Get();
			if (TargetKey->Key == KeyHash) {
				return TargetKey->Data;
			}
			m_pData->At(HashIndex).Slide();
		}

		return 0;
	}

	template <class Type>
	HashMap<Type>::~HashMap() {
		delete m_pData;
	}

}