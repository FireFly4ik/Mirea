package main

import (
	"fmt"
	"math"
)

var mas [6]int32
var k int32 = 0

func main() {
	for i := 0; i < 6; i++ {
		fmt.Scan(&mas[i])
	}
	for {
		k = 0
		for i := 0; i < 5; i++ {
			if math.Abs(float64(mas[i])) > math.Abs(float64(mas[i+1])) {
				mas[i+1], mas[i] = mas[i], mas[i+1]
			} else {
				k += 1
			}
		}
		if k == 5 {
			break
		}
	}
	fmt.Println(mas)
}
