package main

import (
	"bufio"
	"os"
	"slices"
	"strings"
)

var chisla []float32
var oper []string

/*func initialization() {

	var buferChislo float32 = 0
	for x := 0; x < len(virazhenie); x++ {
		if slices.Contains(numbers, string(virazhenie[x])) {
			if num, err := strconv.ParseFloat(string(virazhenie[x]), 32); err == nil {
				buferChislo = buferChislo*10 + float32(num)
			}
		} else {
			if virazhenie[x] == ' ' && buferChislo != 0 {
				chisla = append(chisla, buferChislo)
				buferChislo = 0
			}
			if slices.Contains(operations, string(virazhenie[x])) {
				oper = append(oper, string(virazhenie[x]))
			}
		}
	}
	if buferChislo != 0 {
		chisla = append(chisla, buferChislo)
	}
}*/

func solving(virazhenie string) {
	var numbers = []string{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}
	var operations = []string{"*", "/", "+", "-"}
	for {
		var a, b, aIndex, bIndex int32 = 0, 0, 0, 0
		if strings.Contains(virazhenie, operations[0]) {
			for x := strings.Index(virazhenie, operations[0]) - 1; x > -1; x-- {
				if slices.Contains(numbers, string(virazhenie[x])) {
					a = int32(virazhenie[x])*(10^int32(len(string(a)))) + a
				} else {
					aIndex = int32(x) + 1
					break
				}
			}
			for x := strings.Index(virazhenie, operations[0]) + 1; x > len(virazhenie); x++ {
				if slices.Contains(numbers, string(virazhenie[x])) {
					b = b*10 + int32(virazhenie[x])
				} else {
					bIndex = int32(x)
					break
				}
			}
			virazhenie = virazhenie[:aIndex] + string(a*b) + virazhenie[bIndex:]
		} else {
			break
		}
	}
}

func main() {
	///initialization()
	virazhenie, _ := bufio.NewReader(os.Stdin).ReadString('\n')
	virazhenie = virazhenie[:len(virazhenie)-1]
	for x := 0; x < len(virazhenie); x++ {
		if virazhenie[x] == '(' {
			for y := x + 1; y < len(virazhenie); y++ {
				if virazhenie[y] == '(' {
					break
				} else if virazhenie[y] == ')' {
					solving(virazhenie[x+1 : y])
				}
			}
		}
	}
}
