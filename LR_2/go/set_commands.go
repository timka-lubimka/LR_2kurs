package main

import (
	"fmt"
	"os"
	"sort"
	"strings"
)

func set_commands(file, query string) error {
	if file == "" || query == "" {
		return fmt.Errorf("set_commands needs --file and --query")
	}
	set := newHashTable(false)
	if data, err := os.ReadFile(file); err == nil {
		for _, value := range strings.Fields(string(data)) {
			set.add(value)
		}
	} else if !os.IsNotExist(err) {
		return err
	}
	parts := strings.Fields(query)
	if len(parts) != 2 {
		return fmt.Errorf("query: SETADD/SETDEL/SET_AT value")
	}
	operation, key := parts[0], parts[1]
	switch operation {
	case "SETADD":
		if set.add(key) {
			fmt.Println("ADDED")
		} else {
			fmt.Println("EXISTS")
		}
	case "SETDEL":
		if set.remove(key) {
			fmt.Println("DELETED")
		} else {
			fmt.Println("NOT FOUND")
		}
	case "SET_AT":
		if set.contains(key) {
			fmt.Println("YES")
		} else {
			fmt.Println("NO")
		}
		return nil
	default:
		return fmt.Errorf("unknown set operation")
	}
	items := make([]string, 0, set.count)
	for _, slot := range set.slots {
		if slot.used {
			items = append(items, slot.key)
		}
	}
	sort.Strings(items)
	contents := ""
	if len(items) > 0 {
		contents = strings.Join(items, "\n") + "\n"
	}
	return os.WriteFile(file, []byte(contents), 0644)
}
