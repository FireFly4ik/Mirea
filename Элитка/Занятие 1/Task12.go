package main

import (
	"fmt"
	"math"
)

func prost(q int32) bool {
	var i int32 = 2
	for ; i <= int32(math.Pow(float64(q), 0.5)); i++ {
		if q%i == 0 {
			return false
		}
	}
	return true
}

func main() {
	var a, b int32
	fmt.Scan(&a, &b)
	for i := a; i <= b; i++ {
		if prost(i) {
			fmt.Print(i, " ")
		}
	}
}
