package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"strconv"
	"strings"
)

type Note struct {
	Text string `json:"text"`
}

var notes []Note

func main() {
	// Инициализируем тестовыми данными
	notes = []Note{
		{Text: "First note"},
		{Text: "Second note"},
	}

	http.HandleFunc("/notes", notesHandler)
	http.HandleFunc("/notes/", noteByIdHandler)

	fmt.Println("Server is running on :8080")
	log.Fatal(http.ListenAndServe(":8080", nil))
}

func notesHandler(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case "GET":
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(notes)
	case "POST":
		var newNote Note
		err := json.NewDecoder(r.Body).Decode(&newNote)
		if err != nil {
			http.Error(w, "Invalid request body", http.StatusBadRequest)
			return
		}
		if newNote.Text == "" {
			http.Error(w, "Text field cannot be empty", http.StatusBadRequest)
			return
		}
		notes = append(notes, newNote)
		w.WriteHeader(http.StatusCreated)
		json.NewEncoder(w).Encode(newNote)
	default:
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}

func noteByIdHandler(w http.ResponseWriter, r *http.Request) {
	parts := strings.Split(r.URL.Path, "/")
	if len(parts) < 3 {
		http.Error(w, "Not found", http.StatusNotFound)
		return
	}
	idStr := parts[2]
	id, err := strconv.Atoi(idStr)
	if err != nil || id < 0 || id >= len(notes) {
		http.Error(w, "Note not found", http.StatusNotFound)
		return
	}

	switch r.Method {
	case "GET":
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(notes[id])
	case "DELETE":
		notes = append(notes[:id], notes[id+1:]...)
		w.WriteHeader(http.StatusNoContent)
	default:
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
	}
}
