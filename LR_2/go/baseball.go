package main

import (
	"bufio"
	"fmt"
	"io"
	"strconv"
)

func baseball(r io.Reader) error {
	in := bufio.NewReader(r)
	var operationCount int
	if _, err := fmt.Fscan(in, &operationCount); err != nil || operationCount < 0 {
		return fmt.Errorf("expected operation count")
	}
	var scores Stack
	var total int64
	for i := 0; i < operationCount; i++ {
		var operation string
		if _, err := fmt.Fscan(in, &operation); err != nil {
			return err
		}
		switch operation {
		case "C":
			lastScore, ok := scores.pop()
			if !ok {
				return fmt.Errorf("C requires score")
			}
			score, _ := strconv.ParseInt(lastScore, 10, 64)
			total -= score
		case "D":
			if scores.top == nil {
				return fmt.Errorf("D requires score")
			}
			score, _ := strconv.ParseInt(scores.top.value, 10, 64)
			score *= 2
			scores.push(strconv.FormatInt(score, 10))
			total += score
		case "+":
			if scores.top == nil || scores.top.next == nil {
				return fmt.Errorf("+ requires two scores")
			}
			lastScore, _ := strconv.ParseInt(scores.top.value, 10, 64)
			previousScore, _ := strconv.ParseInt(scores.top.next.value, 10, 64)
			score := lastScore + previousScore
			scores.push(strconv.FormatInt(score, 10))
			total += score
		default:
			score, err := strconv.ParseInt(operation, 10, 64)
			if err != nil || score <= 0 {
				return fmt.Errorf("score must be positive integer")
			}
			scores.push(operation)
			total += score
		}
	}
	fmt.Println(total)
	return nil
}
