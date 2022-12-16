package main

import (
	"fmt"
	// "time"
)

func learnConcurrency() {
	var ch_int = make(chan int)
	var ch_str = make(chan string)

	go func() {
		// time.Sleep(10 * time.Second)
		ch_str <- "jiaoshijie"
	}()

	go func() {
		// time.Sleep(2 * time.Second)
		ch_int <- 2
	}()

	for count := 0; count < 2; {
		fmt.Println("baseline")
		select {
		case o1 := <- ch_int:
			fmt.Println("recive ch_int ", o1)
			count += 1
		case o2 := <- ch_str:
			fmt.Println("recive ch_str ", o2)
			count += 1
		default:
			// fmt.Println("run default code")
		}
	}
}
