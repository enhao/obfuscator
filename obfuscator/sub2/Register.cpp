#include "Obfuscation.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

static void registerObfuscationPass(const PassManagerBuilder &,
                                    legacy::PassManagerBase &PM) {
    PM.add(createObfuscationPass());
}

static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EnabledOnOptLevel0,
                   registerObfuscationPass);

