# Projekt Aufbau
Die Projektstruktur ist bereits vorgegeben und soll nicht verändert werden.

## include
Hier befinden sich alle header (.h) Dateien die mit der Vorgabe mitgeliefert werden. Diese Dateien sollen nicht verändert werden.

## src
Hier befinden sich sowohl bereits mitgelieferte .c Dateien als auch die zu bearbeitenden.
Folgende Dateien sollen bearbeitet werden:
 - src/calloc.c
 - src/mmu.c

Alle anderen Dateien sollen nicht verändert werden und werden auch nicht mit abgegeben!!!

## tests
In diesem Ordner befinden sich Tests. Es sind bereits ein paar Tests als Beispiel vorgegeben.
Weitere Tests sollen von euch selbst erstellt werden. Orientiert euch hierbei an den vorgegebenen Test.
Die Makefile erfasst alle `*.c` Dateien, die mit `test_calloc` bzw `test_mmu` im Namen beginnen und im tests Ordner liegen.
Zum bauen und ausführen der Tests siehe unten.

## build
Dieser Ordner wird automatisch erstellt beim Kompilieren (siehe unten `make`).
Hier landen alle Objekt und ausführbare Dateien.

# Makefile
Es wird eine Makefile mit geliefert welche das Bauen und Ausführen der Aufgabe automatisiert. Mit Hilfe des Tools `make` (unter jeder Distribution vorhanden und meistens bereits installiert) können unterschiedliche `targets` ausgeführt werden.
Die Makefile muss von euch NICHT angepasst werden.

## Make targets

### `make all`
Oder auch nur `make`.
Macht `make build` + `make build_tests`.

### `make run`
Auch `make all_tests`.
Baut alle tests und führt diese aus
.
### `make build`
Kompiliert src/calloc.c und src/mmu.c. Dabei wird noch keine ausführbare Datei erstellt.

### `make build_tests`
Kompiliert alle Tests ohne diese auszuführen.

### `make list_tests`
Gibt eine Liste aller vorhandenen Tests aus.

### `make test_*`
Führt nur den angegebenen Test aus. Dabei ist der Name der Test Datei auch gleich dem make target (ohne dem `.c`).
Beispiel: `make test_calloc_alloc`

### `make gdb_test_*`
Führt den angegebenen Test in gdb aus.
Beispiel: `make gdb_test_example_simple`

### `make clean`
Räumt auf.

### `make pack`
Erstellt die Abgabe. Die Abgabe muss mit `make pack` erstellt werden!!!
