package main

import "fmt"

var dl1, dl2 int32

func main() {
	fmt.Print("Введите длины массива через пробел: ")
	fmt.Scan(&dl1, &dl2)
	mas1 := make([]int32, dl1)
	mas2 := make([]int32, dl2)
	var i int32 = 0
	fmt.Print("Введите элементы первого массива через пробел: ")
	for ; i < dl1; i++ {
		fmt.Scan(&mas1[i])
	}
	i = 0
	fmt.Print("Введите элементы второго массива через пробел: ")
	for ; i < dl2; i++ {
		fmt.Scan(&mas2[i])
	}
	mas3 := make([]int32, 0)
	for {
		if len(mas1) == 0 && len(mas2) == 0 {
			break
		}
		if len(mas1) == 0 {
			mas3 = append(mas3, mas2[0])
			mas2 = mas2[1:]
			continue
		}
		if len(mas2) == 0 {
			mas3 = append(mas3, mas1[0])
			mas1 = mas1[1:]
			continue
		}
		if mas1[0] > mas2[0] {
			mas3 = append(mas3, mas2[0])
			mas2 = mas2[1:]
		} else {
			mas3 = append(mas3, mas1[0])
			mas1 = mas1[1:]
		}
	}
	fmt.Println(mas3)
}
