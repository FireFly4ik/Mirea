package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"unicode"
)

func removePunctuation(str string) string {
	var builder strings.Builder
	for _, char := range str {
		if !unicode.IsPunct(char) {
			builder.WriteRune(char)
		} else {
			builder.WriteRune(' ')
		}
	}
	return builder.String()
}

func main() {
	var maxWord string
	str, _ := bufio.NewReader(os.Stdin).ReadString('\n')
	str = str[:len(str)-1]
	str = removePunctuation(str)
	strin := strings.Split(str, " ")
	for _, word := range strin {
		if len(word) > len(maxWord) {
			maxWord = word
		}
	}
	fmt.Print(maxWord)
}
