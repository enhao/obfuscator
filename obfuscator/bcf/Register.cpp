#include "BogusControlFlow.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

static cl::opt<bool>
BogusControlFlow("bcf", cl::init(false), cl::Hidden,
                 cl::ZeroOrMore, cl::desc("inserting bogus control flow"));

static void registerBogusControlFlowPass(const PassManagerBuilder &,
                                         legacy::PassManagerBase &PM) {
    PM.add(createBogus(BogusControlFlow));
}

static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerBogusControlFlowPass);

