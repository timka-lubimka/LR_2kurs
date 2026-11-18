package main

type ListNode struct {
	value string
	next  *ListNode
}

type SingleList struct {
	head *ListNode
	tail *ListNode
	size int
}

func (list *SingleList) addToEnd(value string) {
	node := &ListNode{value: value}
	if list.tail == nil {
		list.head = node
	} else {
		list.tail.next = node
	}
	list.tail = node
	list.size++
}

func (list *SingleList) addToStart(value string) {
	list.head = &ListNode{value: value, next: list.head}
	if list.tail == nil {
		list.tail = list.head
	}
	list.size++
}

func (list *SingleList) contains(value string) bool {
	for node := list.head; node != nil; node = node.next {
		if node.value == value {
			return true
		}
	}
	return false
}

func (list *SingleList) insertAfterValue(target string, value string) bool {
	for node := list.head; node != nil; node = node.next {
		if node.value == target {
			added := &ListNode{value: value, next: node.next}
			node.next = added
			if list.tail == node {
				list.tail = added
			}
			list.size++
			return true
		}
	}
	return false
}

func (list *SingleList) insertBeforeValue(target string, value string) bool {
	if list.head == nil {
		return false
	}
	if list.head.value == target {
		list.addToStart(value)
		return true
	}

	for node := list.head; node.next != nil; node = node.next {
		if node.next.value == target {
			node.next = &ListNode{value: value, next: node.next}
			list.size++
			return true
		}
	}
	return false
}

func (list *SingleList) deleteValue(value string) bool {
	node := list.head
	var previous *ListNode

	for node != nil && node.value != value {
		previous = node
		node = node.next
	}
	if node == nil {
		return false
	}

	if previous == nil {
		list.head = node.next
	} else {
		previous.next = node.next
	}
	if list.tail == node {
		list.tail = previous
	}
	list.size--
	return true
}

func (list *SingleList) deleteHead() bool {
	if list.head == nil {
		return false
	}
	list.head = list.head.next
	if list.head == nil {
		list.tail = nil
	}
	list.size--
	return true
}

func (list *SingleList) deleteTail() bool {
	if list.tail == nil {
		return false
	}
	if list.head == list.tail {
		list.head = nil
		list.tail = nil
		list.size = 0
		return true
	}

	node := list.head
	for node.next != list.tail {
		node = node.next
	}
	node.next = nil
	list.tail = node
	list.size--
	return true
}

func (list *SingleList) deleteAfterValue(value string) bool {
	for node := list.head; node != nil; node = node.next {
		if node.value == value && node.next != nil {
			removed := node.next
			node.next = removed.next
			if list.tail == removed {
				list.tail = node
			}
			list.size--
			return true
		}
	}
	return false
}

func (list *SingleList) deleteBeforeValue(value string) bool {
	if list.head == nil || list.head == list.tail {
		return false
	}
	if list.head.next.value == value {
		return list.deleteHead()
	}

	for node := list.head; node.next != nil && node.next.next != nil; node = node.next {
		if node.next.next.value == value {
			node.next = node.next.next
			list.size--
			return true
		}
	}
	return false
}
