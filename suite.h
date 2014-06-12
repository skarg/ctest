// suite.h
#ifndef SUITE_H
#define SUITE_H
#include "../TestSuite/Test.h"
#include <vector>
using std::vector;
 class TestSuiteError;

class Suite {
public:
 Suite(const string& name, ostream* osptr = &cout);
 string getName() const;
 long getNumPassed() const;
 long getNumFailed() const;
 const ostream* getStream() const;
 void setStream(ostream* osptr);
 void addTest(Test* t) throw (TestSuiteError);
 void addSuite(const Suite&)
 throw(TestSuiteError);
 void run(); // Calls Test::run() repeatedly
 long report() const;
 void free(); // Deletes tests
private:
 string name;
 ostream* osptr;
 vector<Test*> tests;
 void reset();
 // Disallowed ops:
 Suite(const Suite&);
 Suite& operator=(const Suite&);
};

inline
Suite::Suite(const string& name, ostream* osptr)
 : name(name) {
 this->osptr = osptr;
}

inline string Suite::getName() const {
 return name;
}

inline const ostream* Suite::getStream() const {
 return osptr;
}

inline void Suite::setStream(ostream* osptr) {
 this->osptr = osptr;
}
#endif
