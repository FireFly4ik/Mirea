package main

import (
	"fmt"
)

var chislo, nach, kon, itog int32

func vich(chislo, systemaN, systemaK int32) (vozvrat int32) {
	var stepen int32 = 0
	vozvrat = 0
	for {
		if chislo == 0 {
			break
		}
		var i int32 = 0
		var plus int32 = chislo % systemaK
		for ; i < stepen; i++ {
			plus *= systemaN
		}
		vozvrat += plus
		chislo /= systemaK
		stepen++
	}
	return vozvrat
}

func main() {
	fmt.Scan(&chislo, &nach, &kon)
	var vDes int32 = vich(chislo, nach, 10)
	itog = vich(vDes, 10, kon)
	fmt.Println(itog)
}
