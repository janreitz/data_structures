#pragma once

#include <memory>
#include <stack>

using namespace std;

template<typename T> class DancingList;

template<typename T>
class DLElement
{
public:
	T value() const;
	shared_ptr<DLElement<T>> left() const;
	shared_ptr<DLElement<T>> right() const;

private:
	T m_value;
	shared_ptr<DLElement<T>> m_left;
	shared_ptr<DLElement<T>> m_right;

	template<typename T> friend class DancingList;
};

enum class OperationType
{
	removal, 
	insertion
};

template<typename T>
class Operation
{
public:
	Operation(OperationType t, shared_ptr<DLElement<T>> e);
	OperationType m_type;
	shared_ptr<DLElement<T>> m_element;
};

template<typename T>
class DancingList
{
public:
	DancingList();

	shared_ptr<DLElement<T>> begin() const;
	shared_ptr<DLElement<T>> end() const;
	void remove(shared_ptr<DLElement<T>> e);
	void insertAfter(shared_ptr<DLElement<T>> e, const T& val);
	void undo();

private:
	shared_ptr<DLElement<T>> m_head;
	stack<Operation<T>> m_ops;
};

#include "dancing_list.hpp"