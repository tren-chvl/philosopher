#!/bin/bash

BIN=./philo

if [ ! -f "$BIN" ]; then
    echo "❌ Erreur : l'exécutable '$BIN' n'existe pas."
    echo "Compile ton projet avec : make re"
    exit 1
fi

run_test() {
    CMD="$BIN $1"
    EXPECT="$2"
    DESC="$3"

    # Timeout augmenté pour NB_DIN
    OUTPUT=$(timeout 10 $CMD 2>&1)
    EXIT=$?

    # ----- Tests d'erreur d'arguments -----
    if [[ "$EXPECT" == "error" ]]; then
        if echo "$OUTPUT" | grep -qi "error"; then
            echo "✔️  $DESC : PASS"
        else
            echo "❌ $DESC : FAIL (no error)"
        fi
        return
    fi

    # ----- Tests de mort attendue du philo 1 -----
    if [[ "$EXPECT" == "die1" ]]; then
        if echo "$OUTPUT" | grep -q "1 died"; then
            echo "✔️  $DESC : PASS"
        else
            echo "❌ $DESC : FAIL (did not stop or wrong philo died)"
        fi
        return
    fi

    # ----- Tests NB_DIN -----
    if [[ "$EXPECT" == "stop" ]]; then
        if [ $EXIT -eq 124 ]; then
            echo "❌ $DESC : FAIL (timeout, did not stop)"
        elif echo "$OUTPUT" | grep -q "died"; then
            echo "❌ $DESC : FAIL (a philosopher died)"
        else
            echo "✔️  $DESC : PASS"
        fi
        return
    fi

    # ----- Tests où personne ne doit mourir -----
    if [[ "$EXPECT" == "run" ]]; then
        if echo "$OUTPUT" | grep -q "died"; then
            echo "❌ $DESC : FAIL (should not die)"
        else
            echo "✔️  $DESC : PASS"
        fi
        return
    fi
}

echo "===== TEST ARGUMENTS ====="
run_test "" error "No args"
run_test "10" error "Not enough args"
run_test "10 10" error "Not enough args"
run_test "10 10 10" error "Not enough args"
run_test "10 10 10 10 10 10" error "Too many args"
run_test "-5 600 200 200" error "Negative arg"
run_test "4 -5 200 200" error "Negative arg"
run_test "4 600 -5 200" error "Negative arg"
run_test "4 600 200 -5" error "Negative arg"
run_test "0 0 0 0" error "Zero args"

echo ""
echo "===== TEST MORT ATTENDUE ====="
run_test "1 800 200 200" die1 "1 philo must die"
run_test "4 310 200 100" die1 "Philo 1 must die"
run_test "4 200 205 200" die1 "Philo 1 must die"

echo ""
echo "===== TEST NB_DIN ====="
run_test "4 410 201 200 10" stop "All must eat 10 times"
run_test "5 800 201 200 7" stop "All must eat 7 times"

echo ""
echo "===== TEST PAS DE MORT ====="
run_test "4 410 200 200" run "Should run without death"
run_test "5 600 150 150" run "Should run without death"
run_test "5 800 200 200" run "Should run without death"
run_test "100 800 200 200" run "Should run without death"
run_test "200 800 200 200" run "Should run without death"
run_test "105 800 200 200" run "Should run without death"

echo ""
echo "===== FIN DES TESTS ====="
