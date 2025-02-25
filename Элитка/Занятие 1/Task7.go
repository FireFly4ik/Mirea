package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	str, _ := bufio.NewReader(os.Stdin).ReadString('\n')
	str = str[:len(str)-1]
	q := 0
	for i := 0; i < len(str)/2; i++ {
		if str[i] != str[len(str)-i-1] {
			fmt.Print("Строка не палиндром")
			q = 1
			break
		}
	}
	if q == 0 {
		fmt.Print("Строка палиндром")
	}
}
