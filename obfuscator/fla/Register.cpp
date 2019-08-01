#include "Flattening.h"
#include "Split.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

static cl::opt<bool>
Flattening("fla", cl::init(false), cl::Hidden,
           cl::ZeroOrMore, cl::desc("Call graph flattening"));

static cl::opt<bool>
SplitBasicBlock("split", cl::init(false), cl::Hidden,
                cl::ZeroOrMore, cl::desc("BasicBlock splitting"));

static void registerFlatteningPass(const PassManagerBuilder &,
                                   legacy::PassManagerBase &PM) {
    PM.add(createFlattening(Flattening));
    PM.add(createSplitBasicBlock(Flattening));
}

static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerFlatteningPass);

