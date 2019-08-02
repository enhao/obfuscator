// For open-source license, please refer to [License](https://github.com/HikariObfuscator/Hikari/wiki/License).
//===----------------------------------------------------------------------===//
/*
  Hikari 's own "Pass Scheduler".
  Because currently there is no way to add dependency to transform passes
  Ref : http://lists.llvm.org/pipermail/llvm-dev/2011-February/038109.html
*/
#include "Obfuscation.h"
#include <iostream>
using namespace llvm;
using namespace std;
// Begin Obfuscator Options
static cl::opt<uint64_t> AesSeed("aesSeed", cl::init(0x1337),
                                    cl::desc("seed for the PRNG"));
static cl::opt<bool>
    EnableSubstitution("enable-subobf", cl::init(false), cl::NotHidden,
                       cl::desc("Enable Instruction Substitution."));
static cl::opt<bool> EnableAllObfuscation("enable-allobf", cl::init(false),
                                          cl::NotHidden,
                                          cl::desc("Enable All Obfuscation."));
// End Obfuscator Options

static void LoadEnv() {
 if (getenv("SUBOBF")) {
   EnableSubstitution = true;
 }
 if (getenv("ALLOBF")) {
   EnableAllObfuscation = true;
 }
}
namespace llvm {
struct Obfuscation : public ModulePass {
  static char ID;
  Obfuscation() : ModulePass(ID) {}
  StringRef getPassName() const override {
    return StringRef("HikariObfuscationScheduler");
  }
  bool runOnModule(Module &M) override {
    // Now perform Function-Level Obfuscation
    for (Module::iterator iter = M.begin(); iter != M.end(); iter++) {
      Function &F = *iter;
      if (!F.isDeclaration()) {
        FunctionPass *P = NULL;
        P = createSubstitutionPass(EnableAllObfuscation || EnableSubstitution);
        P->runOnFunction(F);
        delete P;
      }
    }
    errs() << "Doing Post-Run Cleanup\n";
    vector<Function *> funcs;
    for (Module::iterator iter = M.begin(); iter != M.end(); iter++) {
      funcs.push_back(&*iter);
    }
    // Cleanup Flags
    vector<Function *> toDelete;
    for (Module::iterator iter = M.begin(); iter != M.end(); iter++) {
      Function &F = *iter;
      if (F.isDeclaration() && F.hasName() &&
          F.getName().contains("hikari_")) {
        for (User *U : F.users()) {
          if (Instruction *Inst = dyn_cast<Instruction>(U)) {
            Inst->eraseFromParent();
          }
        }
        toDelete.push_back(&F);
      }
    }
    for (Function *F : toDelete) {
      F->eraseFromParent();
    }
    errs() << "Hikari Out\n";
    return true;
  } // End runOnModule
};
ModulePass *createObfuscationPass() {
  LoadEnv();
  if (AesSeed!=0x1337) {
    cryptoutils->prng_seed(AesSeed);
  }
  else{
    cryptoutils->prng_seed();
  }
  return new Obfuscation();
}
} // namespace llvm
char Obfuscation::ID = 0;
INITIALIZE_PASS_BEGIN(Obfuscation, "obfus", "Enable Obfuscation", true, true)
INITIALIZE_PASS_DEPENDENCY(Substitution);
INITIALIZE_PASS_END(Obfuscation, "obfus", "Enable Obfuscation", true, true)
