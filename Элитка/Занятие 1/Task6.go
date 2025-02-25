package main

import (
	"fmt"
	"math"
)

var oper string

func main() {
	var a, b int64
	fmt.Scanln(&a, &b, &oper)
	if oper == "+" {
		fmt.Print(a + b)
	} else if oper == "-" {
		fmt.Print(a - b)
	} else if oper == "*" {
		fmt.Print(a * b)
	} else if oper == "/" {
		fmt.Print(a / b)
	} else if oper == "%" {
		fmt.Print(a % b)
	} else if oper == "^" {
		fmt.Print(math.Pow(float64(a), float64(b)))
	}
}
