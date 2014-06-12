// suite.cpp
#include "Suite.h"
#include <iostream>
#include <stdexcept>
#include <cassert>
using namespace std;

class TestSuiteError : public logic_error {
public:
 TestSuiteError(const string& s = "")
 : logic_error(s) {}
};

void Suite::addTest(Test* t)
 throw(TestSuiteError) {
 // Make sure test has a stream:
 if (t == 0)
 throw TestSuiteError(
 "Null test in Suite::addTest");  else if (osptr != 0 && t->getStream() == 0)
 t->setStream(osptr);
 tests.push_back(t);
 t->reset();
}

void Suite::addSuite(const Suite& s)
 throw(TestSuiteError) {
 for (size_t i = 0; i < s.tests.size(); ++i)
 addTest(s.tests[i]);
}

void Suite::free() {
 // This is not a destructor because tests
 // don't have to be on the heap.
 for (size_t i = 0; i < tests.size(); ++i) {
 delete tests[i];
 tests[i] = 0;
 }
}

void Suite::run() {
 reset();
 for (size_t i = 0; i < tests.size(); ++i) {
 assert(tests[i]);
 tests[i]->run();
 }
}

long Suite::report() const {
 if (osptr) {
 long totFail = 0;
 *osptr << "Suite \"" << name
 << "\"\n=======";
 size_t i;
 for (i = 0; i < name.size(); ++i)
 *osptr << '=';
 *osptr << "=\n";
 for (i = 0; i < tests.size(); ++i) {
 assert(tests[i]);
 totFail += tests[i]->report();
 }
 *osptr << "=======";
 for (i = 0; i < name.size(); ++i)
 *osptr << '=';
 *osptr << "=\n";
 return totFail;
 }
 else
 return getNumFailed();
}

long Suite::getNumPassed() const {
 long totPass = 0;
 for (size_t i = 0; i < tests.size(); ++i) {
 assert(tests[i]);
 totPass += tests[i]->getNumPassed();
 }
 return totPass;
}

long Suite::getNumFailed() const {
 long totFail = 0;
 for (size_t i = 0; i < tests.size(); ++i) {
 assert(tests[i]);  totFail += tests[i]->getNumFailed();
 }
 return totFail;
}

void Suite::reset() {
 for (size_t i = 0; i < tests.size(); ++i) {
 assert(tests[i]);
 tests[i]->reset();
 }
}
