#pragma once

template<typename T>
T DLElement<T>::value() const
{
	return m_value;
}

template<typename T>
shared_ptr<DLElement<T>> DLElement<T>::left() const
{
	return m_left;
}

template<typename T>
shared_ptr<DLElement<T>> DLElement<T>::right() const
{
	return m_right;
}

template<typename T>
Operation<T>::Operation(OperationType t, shared_ptr<DLElement<T>> e)
	: m_type(t)
	, m_element(e)
{

}

template<typename T>
DancingList<T>::DancingList() 
	: m_ops()
{
	m_head = make_shared<DLElement<T>>();
	m_head->m_right = m_head;
	m_head->m_left = m_head;
	return;
}

template<typename T>
shared_ptr<DLElement<T>> DancingList<T>::begin() const
{
	return m_head->m_right;
}

template<typename T>
shared_ptr<DLElement<T>> DancingList<T>::end() const
{
	return m_head->m_left;
}

template<typename T>
void DancingList<T>::remove(shared_ptr<DLElement<T>> e)
{
	auto right = e->m_right;
	auto left = e->m_left;

	right->m_left = left;
	left->m_right = right;

	m_ops.emplace(OperationType::removal, e);
}

template<typename T>
void DancingList<T>::insertAfter(shared_ptr<DLElement<T>> e, const T& val)
{
	auto right = e->m_right;

	auto newElement = make_shared<DLElement<T>>();
	newElement->m_value = val;
	newElement->m_left = e;
	newElement->m_right = right;

	e->m_right = newElement;
	right->m_left = newElement;

	m_ops.emplace(OperationType::insertion, newElement);
}

template<typename T>
void DancingList<T>::undo()
{
	auto op = m_ops.top();

	if (op.m_type == OperationType::removal)
	{
		auto e = op.m_element;
		insertAfter(e->m_left, e->m_value);
	}
	else if (op.m_type == OperationType::insertion)
	{
		remove(op.m_element);
	}
	// I need to pop two times, because the undo operation was also pushed to the stack
	m_ops.pop(); 
	m_ops.pop();
}