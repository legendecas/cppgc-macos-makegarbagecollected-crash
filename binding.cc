#include "node.h"
#include "v8.h"
#include "v8-cppgc.h"
#include "cppgc/garbage-collected.h"
#include "cppgc/allocation.h"

class Test : public cppgc::GarbageCollected<Test> {
 public:
  Test() = default;
  ~Test() = default;

  void Trace(cppgc::Visitor* visitor) const {
    // Implement tracing logic here if needed.
  }

  // Example method to demonstrate functionality.
  int Add(int a, int b) const {
    return a + b;
  }
};

void Init(
    v8::Local<v8::Object> exports,
    v8::Local<v8::Value> module,
    void* priv) {

  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::HandleScope handle_scope(isolate);

  Test* test = cppgc::MakeGarbageCollected<Test>(isolate->GetCppHeap()->GetAllocationHandle());
  test->Add(1, 2);  // Example usage of the Test class.
  // Initialization code for the module goes here.
  // For example, you can add functions or properties to the exports object.
}
NODE_MODULE(binding, Init)
