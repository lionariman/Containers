package main

import (
	"fmt"
	"io"
	"os"
	"sort"
	// "path/filepath"
	// "strings"
)

func inner(out io.Writer, path string, printFiles bool, spaces string) error {
	files, err := os.ReadDir(path)
	if err != nil {
		if printFiles {
			fmt.Fprint(out, spaces+"├───", path, "\n")
		}
		return nil
	}
	sort.Slice(files, func(i, j int) bool {
		return files[i].Name() < files[j].Name()
	})
	for i, f := range files {
		if f.IsDir() {
			if i == len(files)-1 {
				fmt.Fprint(out, spaces+"└───", f.Name(), "\n")
				inner(out, path+"/"+f.Name(), printFiles, spaces+"\t")
			} else {
				fmt.Fprint(out, spaces+"├───", f.Name(), "\n")
				inner(out, path+"/"+f.Name(), printFiles, spaces+"│\t")
			}
		} else {
			if printFiles {
				if i == len(files)-1 {
					fmt.Fprint(out, spaces+"└───", f.Name(), "\n")
				} else {
					fmt.Fprint(out, spaces+"├───", f.Name(), "\n")
				}
			}
		}
	}
	return nil
}

func dirTree(out io.Writer, path string, printFiles bool) error {
	return inner(out, path, printFiles, "")
}

func main() {
	out := os.Stdout
	if !(len(os.Args) == 2 || len(os.Args) == 3) {
		panic("usage go run main.go . [-f]")
	}
	path := os.Args[1]
	printFiles := len(os.Args) == 3 && os.Args[2] == "-f"
	err := dirTree(out, path, printFiles)
	if err != nil {
		panic(err.Error())
	}
}
