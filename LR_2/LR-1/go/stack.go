package main

type Stack struct {
	top  *ListNode
	size int
}

func (stack *Stack) push(value string) {
	stack.top = &ListNode{value: value, next: stack.top}
	stack.size++
}

func (stack *Stack) pop() (string, bool) {
	if stack.top == nil {
		return "", false
	}
	value := stack.top.value
	stack.top = stack.top.next
	stack.size--
	return value, true
}
