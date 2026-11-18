package main

import (
    "flag"
    "os"
)

func main() {
    file := flag.String("file", "", "data file")
    query := flag.String("query", "", "one command")
    flag.Parse()
    if *file == "" || *query == "" {
        usage()
        os.Exit(1)
    }
    runQuery(*file, *query)
}
