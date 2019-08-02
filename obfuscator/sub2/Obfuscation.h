#ifndef _OBFUSCATION_H_
#define _OBFUSCATION_H_
#include "Substitution.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/ModuleUtils.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/NoFolder.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InlineAsm.h"
#include "CryptoUtils.h"
#include "llvm/Transforms/Scalar.h"
#if __has_include("llvm/Transforms/Utils.h")
#include "llvm/Transforms/Utils.h"
#endif
using namespace std;
using namespace llvm;

// Namespace
namespace llvm {
	ModulePass* createObfuscationPass();
	void initializeObfuscationPass(PassRegistry &Registry);
}

#endif
