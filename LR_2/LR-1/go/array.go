package main

type Array struct {
	data []string
}

func (array *Array) addToEnd(value string) {
	array.data = append(array.data, value)
}

func (array *Array) insertAt(index int, value string) bool {
	if index < 0 || index > len(array.data) {
		return false
	}

	array.data = append(array.data, "")
	copy(array.data[index+1:], array.data[index:])
	array.data[index] = value
	return true
}

func (array *Array) getAt(index int) (string, bool) {
	if index < 0 || index >= len(array.data) {
		return "", false
	}
	return array.data[index], true
}

func (array *Array) setAt(index int, value string) bool {
	if index < 0 || index >= len(array.data) {
		return false
	}
	array.data[index] = value
	return true
}

func (array *Array) deleteAt(index int) bool {
	if index < 0 || index >= len(array.data) {
		return false
	}
	array.data = append(array.data[:index], array.data[index+1:]...)
	return true
}
