package main

import "fmt"

func main() {
	var maximum, pred, predpred int32
	fmt.Scan(&maximum)
	predpred = 1
	pred = 1
	fmt.Print("1 1 ")
	for {
		if pred+predpred > maximum {
			break
		}
		fmt.Print(pred+predpred, " ")
		pred, predpred = pred+predpred, pred
	}
}
