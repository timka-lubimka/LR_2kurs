package main

type DoubleNode struct {
	value string
	prev  *DoubleNode
	next  *DoubleNode
}

type DoubleList struct {
	head *DoubleNode
	tail *DoubleNode
	size int
}

func (list *DoubleList) addToEnd(value string) {
	node := &DoubleNode{value: value, prev: list.tail}
	if list.tail == nil {
		list.head = node
	} else {
		list.tail.next = node
	}
	list.tail = node
	list.size++
}

func (list *DoubleList) addToStart(value string) {
	node := &DoubleNode{value: value, next: list.head}
	if list.head == nil {
		list.tail = node
	} else {
		list.head.prev = node
	}
	list.head = node
	list.size++
}

func (list *DoubleList) contains(value string) bool {
	for node := list.head; node != nil; node = node.next {
		if node.value == value {
			return true
		}
	}
	return false
}

func (list *DoubleList) insertAfterValue(target string, value string) bool {
	for node := list.head; node != nil; node = node.next {
		if node.value == target {
			added := &DoubleNode{value: value, prev: node, next: node.next}
			if node.next == nil {
				list.tail = added
			} else {
				node.next.prev = added
			}
			node.next = added
			list.size++
			return true
		}
	}
	return false
}

func (list *DoubleList) insertBeforeValue(target string, value string) bool {
	for node := list.head; node != nil; node = node.next {
		if node.value == target {
			added := &DoubleNode{value: value, prev: node.prev, next: node}
			if node.prev == nil {
				list.head = added
			} else {
				node.prev.next = added
			}
			node.prev = added
			list.size++
			return true
		}
	}
	return false
}

func (list *DoubleList) removeNode(node *DoubleNode) {
	if node.prev == nil {
		list.head = node.next
	} else {
		node.prev.next = node.next
	}
	if node.next == nil {
		list.tail = node.prev
	} else {
		node.next.prev = node.prev
	}
	list.size--
}

func (list *DoubleList) deleteValue(value string) bool {
	for node := list.head; node != nil; node = node.next {
		if node.value == value {
			list.removeNode(node)
			return true
		}
	}
	return false
}

func (list *DoubleList) deleteHead() bool {
	if list.head == nil {
		return false
	}
	list.removeNode(list.head)
	return true
}

func (list *DoubleList) deleteTail() bool {
	if list.tail == nil {
		return false
	}
	list.removeNode(list.tail)
	return true
}

func (list *DoubleList) deleteAfterValue(value string) bool {
	for node := list.head; node != nil; node = node.next {
		if node.value == value && node.next != nil {
			list.removeNode(node.next)
			return true
		}
	}
	return false
}

func (list *DoubleList) deleteBeforeValue(value string) bool {
	for node := list.head; node != nil; node = node.next {
		if node.value == value && node.prev != nil {
			list.removeNode(node.prev)
			return true
		}
	}
	return false
}
