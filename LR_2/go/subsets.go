package main

import (
	"bufio"
	"fmt"
	"io"
)

func subsets(reader io.Reader) error {
	in := bufio.NewReader(reader)
	var count int
	if _, err := fmt.Fscan(in, &count); err != nil || count < 0 || count > 20 {
		return fmt.Errorf("N must be 0..20")
	}
	var values Array
	seen := newHashTable(false)
	for i := 0; i < count; i++ {
		var value string
		if _, err := fmt.Fscan(in, &value); err != nil {
			return err
		}
		if !seen.add(value) {
			return fmt.Errorf("duplicate value")
		}
		values.addToEnd(value)
	}
	for mask := 0; mask < (1 << count); mask++ {
		fmt.Print("{")
		first := true
		for index := 0; index < count; index++ {
			if mask&(1<<index) != 0 {
				if !first {
					fmt.Print(" ")
				}
				value, _ := values.getAt(index)
				fmt.Print(value)
				first = false
			}
		}
		fmt.Println("}")
	}
	return nil
}
