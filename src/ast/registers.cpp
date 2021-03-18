#include "ast.hpp"
/*
$zero $0 Zero
$at $1 Assembler temp
$v0-$v1 $2-3 Value (return from function)
$a0-$a3 $4-7 Argument (to function)
$t0-$t7 $8-15 Temporaries
$s0-$s7 $16-23 Saved Temporaries Saved (Callee saves them)
$t8-$t9 $24-25 Temporaries  (Caller saves them)
$k0-$k1 $26-27 Kernel (OS) Registers
$gp $28 Global Pointer Saved
$sp $29 Stack Pointer Saved
$fp $30 Frame Pointer Saved
$ra $31 Return Address Saved
*/