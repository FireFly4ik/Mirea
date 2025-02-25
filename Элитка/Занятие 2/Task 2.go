package main

import (
	"bufio"
	"os"
	"strconv"
	"strings"
)

func in(letter string) bool {
	var arr = [4]string{"+", "-", "*", "/"}
	for i := 0; i < len(arr); i++ {
		if arr[i] == letter {
			return true
		}
	}
	return false
}

func main() {
	str, _ := bufio.NewReader(os.Stdin).ReadString('\n')
	stroka := strings.Split(str, " ")
	var chisla []int
	stroka[len(stroka)-1] = stroka[len(stroka)-1][:len(stroka[len(stroka)-1])-1]
	for i := 0; i < len(stroka); i++ {
		if in(stroka[i]) {
			switch stroka[i] {
			case "+":
				chisla[len(chisla)-2] = chisla[len(chisla)-2] + chisla[len(chisla)-1]
				chisla = chisla[:len(chisla)-1]
				break
			case "-":
				chisla[len(chisla)-2] = chisla[len(chisla)-2] - chisla[len(chisla)-1]
				chisla = chisla[:len(chisla)-1]
				break
			case "*":
				chisla[len(chisla)-2] = chisla[len(chisla)-2] * chisla[len(chisla)-1]
				chisla = chisla[:len(chisla)-1]
				break
			case "/":
				chisla[len(chisla)-2] = chisla[len(chisla)-2] / chisla[len(chisla)-1]
				chisla = chisla[:len(chisla)-1]
				break
			}
		} else {
			num, _ := strconv.Atoi(stroka[i])
			chisla = append(chisla, num)
		}
	}
	println(chisla[0])
}
