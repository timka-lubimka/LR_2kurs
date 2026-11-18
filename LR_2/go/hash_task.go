package main

import (
	"bufio"
	"fmt"
	"io"
	"strconv"
	"strings"
	"time"
)

func fold(key string) (int64, error) {
	if key == "" {
		return 0, fmt.Errorf("empty number")
	}
	var sum int64
	for i := 0; i < len(key); i += 3 {
		end := i + 3
		if end > len(key) {
			end = len(key)
		}
		for j := i; j < end; j++ {
			if key[j] < '0' || key[j] > '9' {
				return 0, fmt.Errorf("fold key must be decimal")
			}
		}
		foldedKey, err := strconv.ParseInt(key[i:end], 10, 64)
		if err != nil {
			return 0, err
		}
		sum += foldedKey
	}
	return sum, nil
}
func hash_task(reader io.Reader) error {
	in := bufio.NewReader(reader)
	var key string
	if _, err := fmt.Fscan(in, &key); err != nil {
		return err
	}
	foldedKey, err := fold(key)
	if err != nil {
		return err
	}
	parts := []string{}
	for i := 0; i < len(key); i += 3 {
		end := i + 3
		if end > len(key) {
			end = len(key)
		}
		parts = append(parts, key[i:end])
	}
	fmt.Printf("Fold: %s = %d\n", strings.Join(parts, "+"), foldedKey)
	keys := []string{strconv.FormatInt(foldedKey, 10)}
	var extraCount int
	if _, err := fmt.Fscan(in, &extraCount); err == nil {
		if extraCount < 0 {
			return fmt.Errorf("negative N")
		}
		for i := 0; i < extraCount; i++ {
			var key string
			if _, err := fmt.Fscan(in, &key); err != nil {
				return err
			}
			foldedValue, err := fold(key)
			if err != nil {
				return err
			}
			keys = append(keys, strconv.FormatInt(foldedValue, 10))
		}
	}
	for _, useDoubleHash := range []bool{false, true} {
		table := newHashTable(useDoubleHash)
		start := time.Now()
		for _, key := range keys {
			table.add(key)
		}
		for _, key := range keys {
			if !table.contains(key) {
				return fmt.Errorf("hash table failure")
			}
		}
		elapsedMicroseconds := time.Since(start).Microseconds()
		name := "Linear probing"
		if useDoubleHash {
			name = "Double hashing"
		}
		fmt.Printf("%s: count=%d collisions=%d probes=%d time_us=%d\n", name, table.count, table.collisions, table.probes, elapsedMicroseconds)
	}
	return nil
}
