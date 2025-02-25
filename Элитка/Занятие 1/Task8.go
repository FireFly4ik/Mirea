package main

import "fmt"

func main() {
	var a1, a2, b1, b2, c1, c2 int32
	fmt.Println("Введите первую пару чисел")
	fmt.Scanln(&a1, &a2)
	fmt.Println("Введите вторую пару чисел")
	fmt.Scanln(&b1, &b2)
	fmt.Println("Введите третью пару чисел")
	fmt.Scanln(&c1, &c2)
	if a1 < b1 && a2 < b1 {
		fmt.Print(false)
	} else if b1 < a1 && b2 < a1 {
		fmt.Print(false)
	} else if c1 < a1 && c2 < a1 {
		fmt.Print(false)
	} else if a1 < c1 && a2 < c1 {
		fmt.Print(false)
	} else if b1 < c1 && b2 < c1 {
		fmt.Print(false)
	} else if c1 < b1 && c2 < b1 {
		fmt.Print(false)
	} else {
		fmt.Print(true)
	}
}
