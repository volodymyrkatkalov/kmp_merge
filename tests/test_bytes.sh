#!/usr/bin/env bash
set -euo pipefail

BIN=./kmp_merge
TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT

printf '\x01\x02\x03\x04' > "$TMP/a"
printf '\x03\x04\x05\x06' > "$TMP/b"
printf '\x05\x06\x07\x08' > "$TMP/c"
printf '\x01\x02\x03\x04\x05\x06\x07\x08' > "$TMP/expected"

$BIN "$TMP/a" "$TMP/b" > "$TMP/ab"
$BIN "$TMP/ab" "$TMP/c" > "$TMP/out"

cmp -s "$TMP/out" "$TMP/expected" && echo "PASS"
