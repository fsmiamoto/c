package main

import (
	"fmt"
	"io/ioutil"
	"net"
	"os"
	"time"
)

func requestFile(filename string) {
	start := time.Now()
	conn, err := net.Dial("tcp", "localhost:8989")
	if err != nil {
		fmt.Fprintf(os.Stderr, "Failed to connect: %v \n", err)
		return
	}

	_, err = conn.Write([]byte(filename + "\n"))
	if err != nil {
		fmt.Fprintf(os.Stderr, "Failed to write: %v", err)
	}

	_, err = ioutil.ReadAll(conn)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Failed to read: %v", err)
	}

	fmt.Println("Elapsed: ", time.Since(start), filename)
}

func main() {
	requestFile(os.Args[1])
}
