#include "opfuncs.hxx"

void LD_nn_n(ByteLdArgs ldArgs) {
    word loadByte = ldArgs.mmu->get(*ldArgs.pc);
    *ldArgs.reg = loadByte;
}

void LD_r1_r2(ByteRegLdArgs ldArgs) {
    *ldArgs.reg1 = *ldArgs.reg2;
}