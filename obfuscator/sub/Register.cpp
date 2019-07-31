#include "Substitution.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

static void registerSubstitutionPass(const PassManagerBuilder &,
                                     legacy::PassManagerBase &PM) {
    PM.add(createSubstitution(true));
}

static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerSubstitutionPass);

