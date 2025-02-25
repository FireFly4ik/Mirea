package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func vyvodPolya(pole [][]int) {
	for i := 0; i < len(pole); i++ {
		fmt.Println(pole[i])
	}
}

func main() {
	var pole = make([][]int, 10)
	for i := 0; i < len(pole); i++ {
		for j := 0; j < 10; j++ {
			pole[i] = append(pole[i], 0)
		}
	}
	for {
		fmt.Print("Введите координаты клетки: ")
		str, _ := bufio.NewReader(os.Stdin).ReadString('\n')
		koords := strings.Split(str, " ")
		koords[len(koords)-1] = koords[len(koords)-1][:len(koords[len(koords)-1])-1]
		if koords[0] == "-1" {
			break
		}
		y, _ := strconv.Atoi(koords[0])
		x, _ := strconv.Atoi(koords[1])
		pole[x-1][y-1] = 1
	}
}
