# JSON test file format

## basic information

* `instruction` : the name of the instruction during the test
* `size` : the size of the instruction in bytes. This is required in the test to update the PC correctly.

## init

The init section gives default values for registers only once at startup:

```JSON
"init": {
  "sp": "0x8",
  "lr": "0xdead"
}
```
## test execution
Test generation is based on both the simulation and real execution of one instruction with different cases. The 2 main properties are `src` and `dest`, which gives register value (no difference between `src` and `dest`):

```JSON
"src":
{
  "Rm" : {
    "idx": ["r0","r2","r7"],
    "val": ["0", "0x12345678", "0xffffffff", "0xac533c5a", "0xaaaa5555"]
  },
  "imm3": {
    "imm": [0, "0x5", "0x6", "0x7"]
  }
}
```
It sets the register `Rm` (used in the mnemonic), with different reg numbers:

 * `idx` is used in the mnemonic
 * `val` stores the different values for each `idx`

Previous example leads to multiply the number of tests to 3x5=15 cases.

They can also have immediat values. Here, the `imm3` is used in the mnemonic, and the `imm` is a keyword.

## Memory
### data embbeded in code (i.e. to a label)

The `codeData` keyword is used:
```JSON
"codeData": {
  "post": ["0", "0x23456789", "0xffffffff", "0xac578c5a", "0xaaaa555c"]
}
```
Here, 5 labels are generated at the end of the code (`post`) which implies a positive offset in instruction. It can generate a negative offset with `pre`.
In the mnemonic, the `label` keywrd should be used. The generated code is:

```as
.Label0:
	.word 0
.Label1:
	.word 591751049
.Label2:
...
```
## Mnemonic

The mnemonic is defined with the "mnemo" keyword. Parameters are defined between `{}` and should refer to:
  * a register name -> it will be replaced by the `idx` subset.
  * an immediat value -> il will be replaced by the `imm` subset.
  * a `label` keyword when there is a `codeData` section.

The mnemonic should be recognized by the assembler:
```JSON
"mnemo": "asrs {Rd}, {Rm}, #{imm5}"
```
## Comments
the `note` keyword allows to add a text that may be displayed during the execution of tests.
