# cppgc macOS MakeGarbageCollected Crash

Requirements:
- `node` is built with Xcode <= 16.2 (both clang and SDK) (which is already the case for v22.x)
- Have Xcode >= 16.3 locally

Tested matrix:
- Node compiled with apple clang 17, SDK 15.5, no crash.
- Node compiled with apple clang 16, SDK 15.5, no crash (clang in PATH via `sudo xcode-select -s <path_to>/Xcode_16.2.app`).
- Node compiled with apple clang 16, SDK 15.2, crash (clang in PATH, set `CXX_FLAG=-isysroot $(xcrun --sdk macosx --show-sdk-path)`).
- Node compiled with apple clang 17, SDK 15.2, (not test yet).

With:
- Addon clang 17, SDK 15.5.

## Run locally

Run the following commands to reproduce:

```bash
$ npm install
$ npm run build
$ npm run test
```

Back trace:

```
Thread 0 Crashed::  Dispatch queue: com.apple.main-thread
0   node                          	       0x1059ff67c cppgc::internal::MakeGarbageCollectedTraitInternal::Allocate(cppgc::AllocationHandle&, unsigned long, unsigned short) + 52
1   my_module.node                	       0x10b7c85b8 cppgc::internal::MakeGarbageCollectedTraitInternal::AllocationDispatcher<Test, void, 8ul>::Invoke(cppgc::AllocationHandle&, unsigned long) + 24 (allocation.h:94) [inlined]
2   my_module.node                	       0x10b7c85b8 cppgc::MakeGarbageCollectedTraitBase<Test>::Allocate(cppgc::AllocationHandle&, unsigned long) + 24 (allocation.h:180) [inlined]
3   my_module.node                	       0x10b7c85b8 Test* cppgc::MakeGarbageCollectedTrait<Test>::Call<>(cppgc::AllocationHandle&) + 24 (allocation.h:241) [inlined]
4   my_module.node                	       0x10b7c85b8 Test* cppgc::MakeGarbageCollected<Test>(cppgc::AllocationHandle&) + 24 (allocation.h:280) [inlined]
5   my_module.node                	       0x10b7c85b8 Init(v8::Local<v8::Object>, v8::Local<v8::Value>, void*) + 72 (binding.cc:30)
6   node                          	       0x104e174c8 std::__1::__function::__func<node::binding::DLOpen(v8::FunctionCallbackInfo<v8::Value> const&)::$_0, std::__1::allocator<node::binding::DLOpen(v8::FunctionCallbackInfo<v8::Value> const&)::$_0>, bool (node::binding::DLib*)>::operator()(node::binding::DLib*&&) + 520
7   node                          	       0x104ddcb28 node::Environment::TryLoadAddon(char const*, int, std::__1::function<bool (node::binding::DLib*)> const&) + 132
8   node                          	       0x104e159a8 node::binding::DLOpen(v8::FunctionCallbackInfo<v8::Value> const&) + 552
9   node                          	       0x105a4ef98 Builtins_CallApiCallbackGeneric + 184
10  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
11  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
12  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
13  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
14  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
15  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
16  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
17  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
18  node                          	       0x105a4ac0c Builtins_JSEntryTrampoline + 172
19  node                          	       0x105a4a8f4 Builtins_JSEntry + 148
20  node                          	       0x105187680 v8::internal::(anonymous namespace)::Invoke(v8::internal::Isolate*, v8::internal::(anonymous namespace)::InvokeParams const&) + 1652
21  node                          	       0x105187c74 v8::internal::Execution::CallScript(v8::internal::Isolate*, v8::internal::Handle<v8::internal::JSFunction>, v8::internal::Handle<v8::internal::Object>, v8::internal::Handle<v8::internal::Object>) + 132
22  node                          	       0x105025604 v8::Script::Run(v8::Local<v8::Context>, v8::Local<v8::Data>) + 692
23  node                          	       0x104e4038c node::contextify::ContextifyScript::EvalMachine(v8::Local<v8::Context>, node::Environment*, long long, bool, bool, bool, v8::MicrotaskQueue*, v8::FunctionCallbackInfo<v8::Value> const&)::$_0::operator()() const + 32
24  node                          	       0x104e40248 node::contextify::ContextifyScript::EvalMachine(v8::Local<v8::Context>, node::Environment*, long long, bool, bool, bool, v8::MicrotaskQueue*, v8::FunctionCallbackInfo<v8::Value> const&) + 784
25  node                          	       0x104e3fb7c node::contextify::ContextifyScript::RunInContext(v8::FunctionCallbackInfo<v8::Value> const&) + 1256
26  node                          	       0x105a4ef98 Builtins_CallApiCallbackGeneric + 184
27  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
28  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
29  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
30  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
31  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
32  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
33  node                          	       0x105a4cef0 Builtins_InterpreterEntryTrampoline + 272
34  node                          	       0x105a4ac0c Builtins_JSEntryTrampoline + 172
35  node                          	       0x105a4a8f4 Builtins_JSEntry + 148
36  node                          	       0x105187680 v8::internal::(anonymous namespace)::Invoke(v8::internal::Isolate*, v8::internal::(anonymous namespace)::InvokeParams const&) + 1652
37  node                          	       0x105186fdc v8::internal::Execution::Call(v8::internal::Isolate*, v8::internal::Handle<v8::internal::Object>, v8::internal::Handle<v8::internal::Object>, int, v8::internal::Handle<v8::internal::Object>*) + 120
38  node                          	       0x1050365c8 v8::Function::Call(v8::Local<v8::Context>, v8::Local<v8::Value>, int, v8::Local<v8::Value>*) + 524
39  node                          	       0x104e2bad4 node::builtins::BuiltinLoader::CompileAndCall(v8::Local<v8::Context>, char const*, node::Realm*) + 276
40  node                          	       0x104ee26d0 node::Realm::ExecuteBootstrapper(char const*) + 76
41  node                          	       0x104e09810 node::StartExecution(node::Environment*, char const*) + 52
42  node                          	       0x104e095f4 node::StartExecution(node::Environment*, std::__1::function<v8::MaybeLocal<v8::Value> (node::StartExecutionCallbackInfo const&)>) + 1460
43  node                          	       0x104d563e0 node::LoadEnvironment(node::Environment*, std::__1::function<v8::MaybeLocal<v8::Value> (node::StartExecutionCallbackInfo const&)>, std::__1::function<void (node::Environment*, v8::Local<v8::Value>, v8::Local<v8::Value>)>) + 388
44  node                          	       0x104e9aa18 node::NodeMainInstance::Run() + 176
45  node                          	       0x104e0ca80 node::Start(int, char**) + 600
46  dyld                          	       0x18326eb98 start + 6076
```
