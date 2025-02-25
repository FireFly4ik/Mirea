package main

import "fmt"

func main() {
	var a, t, v0 float64
	fmt.Println("Введите значения a, t, v0 в формате float:")
	fmt.Scan(&a, &t, &v0)
	s := v0*t + a*t*t/2
	fmt.Println("Путь, пройденный телом за время t:", s)
}
