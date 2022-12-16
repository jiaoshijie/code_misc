package main

import "fmt"

type expr interface {
	String() string
}

type callExpr struct {
	name string
	count int
}

type listExpr struct {
	total int
	count int
}

func (e *callExpr) String() string {
	return fmt.Sprintf("map %s %d", e.name, e.count)
}

func (e *listExpr) String() string {
	return fmt.Sprintf("see %d %d", e.total, e.count)
}

func learnInterface() {
	opts := make(map[string]expr)
	opts["call"] = &callExpr{"jiao", 1}
	opts["list"] = &listExpr{2, 3}
	ex := opts["call"]
	if e, ok := ex.(*callExpr); ok {
		fmt.Printf("%d\n", e.count)
	} else {
		fmt.Println("it's not ok!!!")
	}
}
