package main

import (
	"bufio"
	"fmt"
	"os"
)

func findSubstringIndex(str, substr string) int {
	index := -1
	for i := 0; i < len(str)-len(substr); i++ {
		if str[i] == substr[0] {
			q := str[i : i+len(substr)]
			if q == substr {
				index = i
				break
			}
		}
	}
	return index
}

func main() {
	fmt.Print("Введите строку: ")
	str, _ := bufio.NewReader(os.Stdin).ReadString('\n')
	fmt.Print("Введите подстроку: ")
	substr, _ := bufio.NewReader(os.Stdin).ReadString('\n')
	fmt.Println(findSubstringIndex(str[:len(str)-1], substr[:len(substr)-1]))
}
