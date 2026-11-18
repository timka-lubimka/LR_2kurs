package main

import (
	"bufio"
	"fmt"
	"io"
	"strconv"
)

// BST node, not a complete binary tree: LR1 queue is used for level traversal.
type bstNode struct {
	value       int
	left, right *bstNode
}

func right_view(reader io.Reader) error {
	in := bufio.NewReader(reader)
	var count int
	if _, err := fmt.Fscan(in, &count); err != nil || count < 0 {
		return fmt.Errorf("input: N followed by N values")
	}
	var root *bstNode
	for i := 0; i < count; i++ {
		var value int
		if _, err := fmt.Fscan(in, &value); err != nil {
			return err
		}
		current := &root
		for *current != nil {
			if (*current).value == value {
				break
			}
			if value < (*current).value {
				current = &(*current).left
			} else {
				current = &(*current).right
			}
		}
		if *current == nil {
			*current = &bstNode{value: value}
		}
	}
	var queue Queue
	nodes := []*bstNode{}
	if root != nil {
		nodes = append(nodes, root)
		queue.enqueue("0")
	}
	first := true
	for queue.size > 0 {
		levelSize := queue.size
		right := 0
		for i := 0; i < levelSize; i++ {
			indexText, _ := queue.dequeue()
			index, _ := strconv.Atoi(indexText)
			node := nodes[index]
			right = node.value
			if node.left != nil {
				nodes = append(nodes, node.left)
				queue.enqueue(strconv.Itoa(len(nodes) - 1))
			}
			if node.right != nil {
				nodes = append(nodes, node.right)
				queue.enqueue(strconv.Itoa(len(nodes) - 1))
			}
		}
		if !first {
			fmt.Print(" ")
		}
		fmt.Print(right)
		first = false
	}
	fmt.Println()
	return nil
}
