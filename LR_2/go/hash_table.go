package main

// Custom open addressing hash table: expected O(1) operations, amortized resize.
type hashSlot struct {
	key           string
	used, deleted bool
}
type HashTable struct {
	slots                     []hashSlot
	count, probes, collisions int
	double                    bool
}

func newHashTable(useDoubleHash bool) *HashTable {
	return &HashTable{slots: make([]hashSlot, 17), double: useDoubleHash}
}

func hashKey(key string) uint64 {
	hashValue := uint64(14695981039346656037)
	for i := 0; i < len(key); i++ {
		hashValue ^= uint64(key[i])
		hashValue *= 1099511628211
	}
	return hashValue
}

func (table *HashTable) step(key string) int {
	if !table.double {
		return 1
	}
	return 1 + int(hashKey("secondary:"+key)%uint64(len(table.slots)-1))
}

func (table *HashTable) locate(key string) (int, bool) {
	base := int(hashKey(key) % uint64(len(table.slots)))
	step := table.step(key)
	deleted := -1
	for i := 0; i < len(table.slots); i++ {
		index := (base + i*step) % len(table.slots)
		table.probes++
		slot := table.slots[index]
		if slot.used {
			if slot.key == key {
				return index, true
			}
			table.collisions++
		} else if slot.deleted {
			if deleted < 0 {
				deleted = index
			}
		} else {
			if deleted >= 0 {
				return deleted, false
			}
			return index, false
		}
	}
	return deleted, false
}

func isPrime(n int) bool {
	if n < 2 {
		return false
	}
	for divisor := 2; divisor <= n/divisor; divisor++ {
		if n%divisor == 0 {
			return false
		}
	}
	return true
}

func (table *HashTable) rehash() {
	oldSlots := table.slots
	capacity := len(oldSlots)*2 + 1
	for !isPrime(capacity) {
		capacity++
	}
	table.slots = make([]hashSlot, capacity)
	table.count = 0
	for _, slot := range oldSlots {
		if slot.used {
			table.add(slot.key)
		}
	}
}

func (table *HashTable) add(key string) bool {
	if (table.count+1)*10 >= len(table.slots)*7 {
		table.rehash()
	}
	index, found := table.locate(key)
	if found {
		return false
	}
	if index < 0 {
		table.rehash()
		return table.add(key)
	}
	table.slots[index] = hashSlot{key: key, used: true}
	table.count++
	return true
}

func (table *HashTable) contains(key string) bool {
	_, found := table.locate(key)
	return found
}

func (table *HashTable) remove(key string) bool {
	index, found := table.locate(key)
	if !found {
		return false
	}
	table.slots[index] = hashSlot{deleted: true}
	table.count--
	return true
}
