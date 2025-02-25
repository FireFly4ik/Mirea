package main

import (
	"fmt"
	"math"
)

func main() {
	var a int32
	fmt.Scan(&a)
	if float64(a) == math.Pow(float64(a/100), 3)+math.Pow(float64(a%100/10), 3)+math.Pow(float64(a%10), 3) {
		fmt.Print("Это число Армстронга")
	} else {
		fmt.Print("Это не число Армстронга")
	}
}
