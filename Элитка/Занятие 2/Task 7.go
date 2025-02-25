package main

import (
	"fmt"
	"math"
)

func proverka(a int) bool {
	for i := 2; float64(i) <= math.Pow(float64(a), 0.5); i++ {
		if a%i == 0 {
			return false
		}
	}
	return true
}

func main() {
	var a int32
	fmt.Scan(&a)
	if proverka(int(a)) {
		fmt.Println("Простое")
	} else {
		fmt.Println("Составное")
	}
}
