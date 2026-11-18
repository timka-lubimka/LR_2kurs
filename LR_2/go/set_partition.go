package main

import (
	"bufio"
	"fmt"
	"io"
	"sort"
	"strconv"
)

func set_partition(reader io.Reader) error {
	in := bufio.NewReader(reader)
	var count int
	var target int64
	if _, err := fmt.Fscan(in, &count, &target); err != nil || count < 0 || target <= 0 {
		return fmt.Errorf("input: N target followed by N distinct natural numbers")
	}
	set := newHashTable(false)
	var values Array
	numbers := make([]int64, count)
	var total int64
	for i := range numbers {
		if _, err := fmt.Fscan(in, &numbers[i]); err != nil || numbers[i] <= 0 {
			return fmt.Errorf("invalid element")
		}
		if !set.add(strconv.FormatInt(numbers[i], 10)) {
			return fmt.Errorf("duplicate element")
		}
		values.addToEnd(strconv.FormatInt(numbers[i], 10))
		total += numbers[i]
	}
	if count == 0 || total%target != 0 {
		fmt.Println("Impossible")
		return nil
	}
	sort.Slice(numbers, func(i, j int) bool { return numbers[i] > numbers[j] })
	if numbers[0] > target || total/target > int64(count) {
		fmt.Println("Impossible")
		return nil
	}
	groupCount := int(total / target)
	groupSums := make([]int64, groupCount)
	groups := make([][]int64, groupCount)
	var findPartition func(int) bool
	findPartition = func(i int) bool {
		if i == count {
			for _, groupSum := range groupSums {
				if groupSum != target {
					return false
				}
			}
			return true
		}
		for j := 0; j < groupCount; j++ {
			if groupSums[j]+numbers[i] > target {
				continue
			}
			alreadyTried := false
			for h := 0; h < j; h++ {
				if groupSums[h] == groupSums[j] {
					alreadyTried = true
					break
				}
			}
			if alreadyTried {
				continue
			}
			groupSums[j] += numbers[i]
			groups[j] = append(groups[j], numbers[i])
			if findPartition(i + 1) {
				return true
			}
			groups[j] = groups[j][:len(groups[j])-1]
			groupSums[j] -= numbers[i]
			if groupSums[j] == 0 {
				break
			}
		}
		return false
	}
	if !findPartition(0) {
		fmt.Println("Impossible")
	} else {
		for _, group := range groups {
			fmt.Print("{")
			for i, value := range group {
				if i > 0 {
					fmt.Print(" ")
				}
				fmt.Print(value)
			}
			fmt.Println("}")
		}
	}
	return nil
}
