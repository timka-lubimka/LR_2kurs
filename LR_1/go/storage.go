package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

var arrays = map[string]*Array{}
var singleLists = map[string]*SingleList{}
var doubleLists = map[string]*DoubleList{}
var stacks = map[string]*Stack{}
var queues = map[string]*Queue{}

func arrayByName(name string) *Array {
	if arrays[name] == nil {
		arrays[name] = &Array{}
	}
	return arrays[name]
}

func singleListByName(name string) *SingleList {
	if singleLists[name] == nil {
		singleLists[name] = &SingleList{}
	}
	return singleLists[name]
}

func doubleListByName(name string) *DoubleList {
	if doubleLists[name] == nil {
		doubleLists[name] = &DoubleList{}
	}
	return doubleLists[name]
}

func stackByName(name string) *Stack {
	if stacks[name] == nil {
		stacks[name] = &Stack{}
	}
	return stacks[name]
}

func queueByName(name string) *Queue {
	if queues[name] == nil {
		queues[name] = &Queue{}
	}
	return queues[name]
}

func load(path string) {
	file, err := os.Open(path)
	if err != nil {
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		parts := strings.Fields(scanner.Text())
		if len(parts) < 2 {
			continue
		}

		typeName := parts[0]
		name := parts[1]
		switch typeName {
		case "M":
			arrayByName(name)
		case "F":
			singleListByName(name)
		case "L":
			doubleListByName(name)
		case "S":
			stackByName(name)
		case "Q":
			queueByName(name)
		default:
			continue
		}

		for _, value := range parts[2:] {

			switch typeName {
			case "M":
				arrayByName(name).addToEnd(value)
			case "F":
				singleListByName(name).addToEnd(value)
			case "L":
				doubleListByName(name).addToEnd(value)
			case "S":
				stackByName(name).push(value)
			case "Q":
				queueByName(name).enqueue(value)
			}
		}
	}
}

func save(path string) {
	var output strings.Builder

	for name, array := range arrays {
		fmt.Fprintf(&output, "M %s", name)
		for _, value := range array.data {
			fmt.Fprintf(&output, " %s", value)
		}
		output.WriteByte('\n')
	}

	for name, list := range singleLists {
		fmt.Fprintf(&output, "F %s", name)
		for node := list.head; node != nil; node = node.next {
			fmt.Fprintf(&output, " %s", node.value)
		}
		output.WriteByte('\n')
	}

	for name, list := range doubleLists {
		fmt.Fprintf(&output, "L %s", name)
		for node := list.head; node != nil; node = node.next {
			fmt.Fprintf(&output, " %s", node.value)
		}
		output.WriteByte('\n')
	}

	for name, stack := range stacks {
		fmt.Fprintf(&output, "S %s", name)
		values := []string{}
		for node := stack.top; node != nil; node = node.next {
			values = append(values, node.value)
		}
		for i := len(values) - 1; i >= 0; i-- {
			fmt.Fprintf(&output, " %s", values[i])
		}
		output.WriteByte('\n')
	}

	for name, queue := range queues {
		fmt.Fprintf(&output, "Q %s", name)
		for node := queue.front; node != nil; node = node.next {
			fmt.Fprintf(&output, " %s", node.value)
		}
		output.WriteByte('\n')
	}

	_ = os.WriteFile(path, []byte(output.String()), 0644)
}
