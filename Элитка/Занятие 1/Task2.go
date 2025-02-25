package main

import (
	"fmt"
	"math"
)

var a, b, c int32
var x1, x2, disc float64
var xc1, xc2 complex128

func main() {
	fmt.Scan(&a, &b, &c)
	disc = float64(b*b - 4*a*c)
	if disc > 0 {
		x1 = (float64(-1*b) - math.Sqrt(disc)) / float64(2*a)
		x2 = (float64(-1*b) + math.Sqrt(disc)) / float64(2*a)
		fmt.Println(x1, x2)
	} else if disc == 0 {
		x1 = (float64(-1 * b)) / float64(2*a)
		fmt.Println(x1)
	} else {
		xc1 = (complex(float64(b*-1), 0) - complex(0, math.Sqrt(math.Abs(disc)))) / complex(float64(2*a), 0)
		xc2 = (complex(float64(b*-1), 0) + complex(0, math.Sqrt(math.Abs(disc)))) / complex(float64(2*a), 0)
		fmt.Println(xc1, xc2)
	}
}
