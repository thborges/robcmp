#!/usr/bin/env bash
set -euo pipefail

repo_dir="$(cd "$(dirname "$0")/../.." && pwd)"
robcmp_bin="${ROBCMP:-$repo_dir/build/robcmp}"
opt_bin="${OPT:-opt-21}"
work_dir="$(mktemp -d)"
trap 'rm -rf "$work_dir"' EXIT

positive_tests=(
    read_pointer
    write_pointer
    pointer_parameter
    pointer_return
    uninitialized_then_assign
    operators_unchanged
    compound_multiply_unchanged
)
negative_tests=(
    negative_deref_scalar
    negative_incompatible_pointer
    negative_address_rvalue
    negative_scalar_to_pointer
    negative_pointer_to_pointer
)

for test_name in "${positive_tests[@]}"; do
    source_file="$repo_dir/test/pointers/$test_name.rob"
    ir_file="$work_dir/$test_name.ll"
    object_file="$work_dir/$test_name.o"

    "$robcmp_bin" -a stm32f1 -O0 "$source_file" > "$ir_file"
    "$opt_bin" -passes=verify "$ir_file" -disable-output
    "$robcmp_bin" -a stm32f1 -O0 -o "$object_file" "$source_file"
    file "$object_file" | grep -Eq 'ELF 32-bit.*ARM'
    printf 'PASS positive: %s\n' "$test_name"
done

for test_name in "${negative_tests[@]}"; do
    source_file="$repo_dir/test/pointers/$test_name.rob"
    if "$robcmp_bin" -a stm32f1 -O0 "$source_file" > /dev/null 2> "$work_dir/$test_name.err"; then
        printf 'FAIL negative accepted: %s\n' "$test_name" >&2
        exit 1
    fi
    printf 'PASS negative rejected: %s\n' "$test_name"
done
