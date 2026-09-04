# General pointers in ROBL

This branch adds a minimal, typed pointer model without changing the existing
`register T name at address;` feature.

## Syntax

```rob
int32* p;
int32* p = &x;
value = *p;
*p = value;

void update(int32* p) {
    *p = *p + 1;
}

int32* identity(int32* p) {
    return p;
}
```

An uninitialized ROBL pointer declaration is initialized to a typed null
pointer. This deterministic behavior differs from an uninitialized automatic
pointer in C.

## Semantic model

- Every general pointer has a `DataType` whose LLVM representation is opaque
  `ptr` and whose `pointedType` retains the ROBL type being pointed to.
- `&` accepts only addressable AST nodes.
- `*` accepts only a general pointer and produces the retained pointed type.
- Stores through a pointer coerce numeric values using the existing ROBL rules
  and reject incompatible scalar or pointer types.
- Pointer width comes from the selected target's pointer type. LLVM's
  `DataLayout` supplies load/store ABI alignment during IR generation.

## Features intentionally kept separate

- `Pointer` in `Pointer.cpp` still models fixed-address, volatile registers.
- `T[]` remains the array/matrix parameter and reference mechanism, including
  size pseudo-parameters.
- Complex ROBL values retain their existing implicit reference behavior.

## Not supported yet

- pointers to pointers;
- pointer arithmetic;
- function pointers;
- integer/pointer conversions;
- `void*`;
- pointers to arrays or matrices;
- dynamic allocation.

The tests under `test/pointers` cover pointer reads, writes, parameters,
returns, preservation of binary `*` and `&`, and required negative cases.
