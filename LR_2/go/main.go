package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintln(os.Stderr, "Usage: go run . baseball..lru_task [--file ... --query ...]")
		os.Exit(1)
	}
	var err error
	switch os.Args[1] {
	case "baseball":
		err = baseball(os.Stdin)
	case "set_commands":
		file, query := "", ""
		for i := 2; i < len(os.Args); i++ {
			if os.Args[i] == "--file" && i+1 < len(os.Args) {
				i++
				file = os.Args[i]
			} else if os.Args[i] == "--query" && i+1 < len(os.Args) {
				i++
				query = os.Args[i]
			}
		}
		err = set_commands(file, query)
	case "set_partition":
		err = set_partition(os.Stdin)
	case "subsets":
		err = subsets(os.Stdin)
	case "right_view":
		err = right_view(os.Stdin)
	case "hash_task":
		err = hash_task(os.Stdin)
	case "lru_task":
		err = lru_task(os.Stdin)
	default:
		err = fmt.Errorf("unknown task %s", strings.TrimSpace(os.Args[1]))
	}
	if err != nil {
		fmt.Fprintln(os.Stderr, "ERROR:", err)
		os.Exit(1)
	}
}
