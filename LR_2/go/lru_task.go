package main

import (
	"bufio"
	"fmt"
	"io"
)

type cacheValue struct {
	value string
	node  *DoubleNode
}

func lru_task(reader io.Reader) error {
	in := bufio.NewReader(reader)
	var capacity, commandCount int
	if _, err := fmt.Fscan(in, &capacity, &commandCount); err != nil || capacity < 0 || commandCount < 0 {
		return fmt.Errorf("input: capacity Q then operations")
	}
	var order DoubleList
	items := make(map[string]cacheValue)
	touch := func(node *DoubleNode) {
		if node == order.tail {
			return
		}
		if node.prev != nil {
			node.prev.next = node.next
		} else {
			order.head = node.next
		}
		if node.next != nil {
			node.next.prev = node.prev
		}
		node.prev = order.tail
		node.next = nil
		if order.tail != nil {
			order.tail.next = node
		}
		order.tail = node
		if order.head == nil {
			order.head = node
		}
	}
	for i := 0; i < commandCount; i++ {
		var operation, key string
		if _, err := fmt.Fscan(in, &operation, &key); err != nil {
			return err
		}
		switch operation {
		case "GET":
			item, ok := items[key]
			if !ok {
				fmt.Println(-1)
			} else {
				touch(item.node)
				fmt.Println(item.value)
			}
		case "SET":
			var value string
			if _, err := fmt.Fscan(in, &value); err != nil {
				return err
			}
			if capacity == 0 {
				continue
			}
			if old, ok := items[key]; ok {
				old.value = value
				items[key] = old
				touch(old.node)
				continue
			}
			if len(items) == capacity {
				victim := order.head
				delete(items, victim.value)
				order.removeNode(victim)
			}
			order.addToEnd(key)
			items[key] = cacheValue{value, order.tail}
		default:
			return fmt.Errorf("unknown operation %s", operation)
		}
	}
	return nil
}
