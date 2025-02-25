package main

import "fmt"

func main() {
	var a, b float32
	var oper string
	fmt.Scan(&a, &b, &oper)
	switch oper {
	case "+":
		fmt.Println(a + b)
		break
	case "-":
		fmt.Println(a - b)
		break
	case "*":
		fmt.Println(a * b)
		break
	case "/":
		if b == 0 {
			fmt.Println("Деление на 0!")
		} else {
			fmt.Println(a / b)
		}
	}
}
