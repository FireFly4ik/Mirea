package main

import (
	"fmt"
)

func main() {
	var god int32 = 0
	fmt.Scan(&god)
	if god%4 == 0 {
		fmt.Println("Год високосный")
	} else {
		fmt.Println("Год не високосный")
	}
}
