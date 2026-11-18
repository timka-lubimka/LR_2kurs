package main

type Queue struct {
	front *ListNode
	back  *ListNode
	size  int
}

func (queue *Queue) enqueue(value string) {
	node := &ListNode{value: value}
	if queue.back == nil {
		queue.front = node
	} else {
		queue.back.next = node
	}
	queue.back = node
	queue.size++
}

func (queue *Queue) dequeue() (string, bool) {
	if queue.front == nil {
		return "", false
	}
	value := queue.front.value
	queue.front = queue.front.next
	if queue.front == nil {
		queue.back = nil
	}
	queue.size--
	return value, true
}
