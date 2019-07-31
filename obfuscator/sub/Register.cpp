#include "Substitution.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

static cl::opt<bool>
Substitution("sub", cl::init(false), cl::Hidden,
             cl::ZeroOrMore, cl::desc("operators substitution"));

static void registerSubstitutionPass(const PassManagerBuilder &,
                                     legacy::PassManagerBase &PM) {
    PM.add(createSubstitution(Substitution));
}

static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerSubstitutionPass);

