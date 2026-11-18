package main

import (
	"fmt"
	"strconv"
	"strings"
)

func printArray(array *Array) {
	for _, value := range array.data {
		fmt.Printf("%s ", value)
	}
	fmt.Println()
}

func printSingleList(list *SingleList) {
	for node := list.head; node != nil; node = node.next {
		fmt.Printf("%s ", node.value)
	}
	fmt.Println()
}

func printDoubleList(list *DoubleList, reverse bool) {
	if reverse {
		for node := list.tail; node != nil; node = node.prev {
			fmt.Printf("%s ", node.value)
		}
	} else {
		for node := list.head; node != nil; node = node.next {
			fmt.Printf("%s ", node.value)
		}
	}
	fmt.Println()
}

func printStack(stack *Stack) {
	for node := stack.top; node != nil; node = node.next {
		fmt.Printf("%s ", node.value)
	}
	fmt.Println()
}

func printQueue(queue *Queue) {
	for node := queue.front; node != nil; node = node.next {
		fmt.Printf("%s ", node.value)
	}
	fmt.Println()
}

func readNumber(words []string, place int) (int, bool) {
	if place >= len(words) {
		return 0, false
	}
	value, err := strconv.Atoi(words[place])
	return value, err == nil
}

func usage() {
	fmt.Println("See README.md for command examples.")
}

func printItemAt(list *SingleList, index int) bool {
	if index < 0 {
		return false
	}
	for node, i := list.head, 0; node != nil; node, i = node.next, i+1 {
		if i == index {
			fmt.Println(node.value)
			return true
		}
	}
	return false
}

func printDoubleItemAt(list *DoubleList, index int) bool {
	if index < 0 {
		return false
	}
	for node, i := list.head, 0; node != nil; node, i = node.next, i+1 {
		if i == index {
			fmt.Println(node.value)
			return true
		}
	}
	return false
}

func runQuery(file string, query string) {
	load(file)
	words := strings.Fields(query)
	if len(words) < 2 {
		usage()
		return
	}

	command := words[0]
	name := ""
	if len(words) > 1 {
		name = words[1]
	}
	index, hasIndex := readNumber(words, 2)
    first, second := "", ""
    hasFirst, hasSecond := len(words) > 2, len(words) > 3
    if hasFirst { first = words[2] }
    if hasSecond { second = words[3] }
	changed := false
	ok := true

	switch command {
	case "MPUSH":
		if hasFirst { arrayByName(name).addToEnd(first); changed = true } else { ok = false }
	case "MINSERT":
		if hasIndex && hasSecond { ok = arrayByName(name).insertAt(index, second); changed = ok } else { ok = false }
	case "MGET":
		if hasIndex { value, found := arrayByName(name).getAt(index); ok = found; if found { fmt.Println(value) } } else { ok = false }
	case "MDEL":
		if hasIndex { ok = arrayByName(name).deleteAt(index); changed = ok } else { ok = false }
	case "MSET":
		if hasIndex && hasSecond { ok = arrayByName(name).setAt(index, second); changed = ok } else { ok = false }
	case "MLEN":
		fmt.Println(len(arrayByName(name).data))
	case "MPRINT":
		printArray(arrayByName(name))

	case "FPUSH":
		if hasFirst { singleListByName(name).addToEnd(first); changed = true } else { ok = false }
	case "FHEAD":
		if hasFirst { singleListByName(name).addToStart(first); changed = true } else { ok = false }
	case "FBEFORE":
		if hasFirst && hasSecond { ok = singleListByName(name).insertBeforeValue(first, second); changed = ok } else { ok = false }
	case "FAFTER":
		if hasFirst && hasSecond { ok = singleListByName(name).insertAfterValue(first, second); changed = ok } else { ok = false }
	case "FDEL":
		if hasFirst { ok = singleListByName(name).deleteValue(first); changed = ok } else { ok = false }
	case "FDELHEAD":
		ok = singleListByName(name).deleteHead(); changed = ok
	case "FDELTAIL":
		ok = singleListByName(name).deleteTail(); changed = ok
	case "FDELBEFORE":
		if hasFirst { ok = singleListByName(name).deleteBeforeValue(first); changed = ok } else { ok = false }
	case "FDELAFTER":
		if hasFirst { ok = singleListByName(name).deleteAfterValue(first); changed = ok } else { ok = false }
	case "FMEMBER":
		if hasFirst { fmt.Println(strings.ToUpper(strconv.FormatBool(singleListByName(name).contains(first)))) } else { ok = false }
	case "FGET":
		if hasIndex { ok = printItemAt(singleListByName(name), index) } else { ok = false }
	case "FPRINT":
		printSingleList(singleListByName(name))

	case "LPUSH":
		if hasFirst { doubleListByName(name).addToEnd(first); changed = true } else { ok = false }
	case "LHEAD":
		if hasFirst { doubleListByName(name).addToStart(first); changed = true } else { ok = false }
	case "LBEFORE":
		if hasFirst && hasSecond { ok = doubleListByName(name).insertBeforeValue(first, second); changed = ok } else { ok = false }
	case "LAFTER":
		if hasFirst && hasSecond { ok = doubleListByName(name).insertAfterValue(first, second); changed = ok } else { ok = false }
	case "LDEL":
		if hasFirst { ok = doubleListByName(name).deleteValue(first); changed = ok } else { ok = false }
	case "LDELHEAD":
		ok = doubleListByName(name).deleteHead(); changed = ok
	case "LDELTAIL":
		ok = doubleListByName(name).deleteTail(); changed = ok
	case "LDELBEFORE":
		if hasFirst { ok = doubleListByName(name).deleteBeforeValue(first); changed = ok } else { ok = false }
	case "LDELAFTER":
		if hasFirst { ok = doubleListByName(name).deleteAfterValue(first); changed = ok } else { ok = false }
	case "LMEMBER":
		if hasFirst { fmt.Println(strings.ToUpper(strconv.FormatBool(doubleListByName(name).contains(first)))) } else { ok = false }
	case "LGET":
		if hasIndex { ok = printDoubleItemAt(doubleListByName(name), index) } else { ok = false }
	case "LPRINT":
		printDoubleList(doubleListByName(name), false)
	case "LREVERSE":
		printDoubleList(doubleListByName(name), true)

	case "SPUSH":
		if hasFirst { stackByName(name).push(first); changed = true } else { ok = false }
	case "SPOP":
		value, found := stackByName(name).pop(); ok = found; changed = found; if found { fmt.Println(value) }
	case "SGET":
		if stackByName(name).top == nil { ok = false } else { fmt.Println(stackByName(name).top.value) }
	case "SPRINT":
		printStack(stackByName(name))

	case "QPUSH":
		if hasFirst { queueByName(name).enqueue(first); changed = true } else { ok = false }
	case "QPOP":
		value, found := queueByName(name).dequeue(); ok = found; changed = found; if found { fmt.Println(value) }
	case "QGET":
		if queueByName(name).front == nil { ok = false } else { fmt.Println(queueByName(name).front.value) }
	case "QPRINT":
		printQueue(queueByName(name))

	case "PRINT":
		if arrays[name] != nil { printArray(arrays[name])
		} else if singleLists[name] != nil { printSingleList(singleLists[name])
		} else if doubleLists[name] != nil { printDoubleList(doubleLists[name], false)
		} else if stacks[name] != nil { printStack(stacks[name])
		} else if queues[name] != nil { printQueue(queues[name])
		} else { ok = false }
	default:
		usage()
		ok = false
	}

	if !ok {
		fmt.Println("ERROR: invalid command, missing value, or element not found")
	}
	if changed {
		save(file)
	}
}
