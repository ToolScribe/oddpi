// -*- C++ -*-

// Copyright (c) 2014, ToolScribe
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
// 
// * Neither the name of oddpi nor the names of its contributors may be
//   used to endorse or promote products derived from this software
//   without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.


#include "obj.h"

using namespace llvm;

namespace ToolScribe {
  namespace ODD {

    std::string Object::nameKey = "NAME";
    std::string Object::kindKey = "KIND";
    std::string Object::refKey = "_REFCNT";

    Object::Object(std::string name, std::string kind) {
      prop = new Dictionary();
      
      Value *val = new Value(new std::string(name));
      PropValues& vList = (*prop)[Object::nameKey];
      vList.insert(vList.begin(),*val);

      val = new Value(new long(1));
      vList = (*prop)[Object::refKey];
      vList.insert(vList.begin(),*val);

      val = new Value(new std::string(kind));
      vList = (*prop)[Object::kindKey];
      vList.insert(vList.begin(),*val);
    }

    Object::Object(Object& src) {
      PropValues& vList = (*(src.prop))[Object::refKey];
      long *refcnt = (vList.begin())->get<long*>();
      ++(*refcnt);
      prop = src.prop;
    }

    Object& Object::operator=(Object& src) {
      PropValues& vList = (*(src.prop))[Object::refKey];
      long *refcnt = (vList.begin())->get<long*>();
      ++(*refcnt);
      
      vList = (*prop)[Object::refKey];
      refcnt = (vList.begin())->get<long*>();
      if (--refcnt == 0)
	delete prop;
      prop = src.prop;
      return *this;
    }

    bool Object::exists(std::string pName) {
      Object::Dictionary::iterator p = prop->find(pName);
      return p != prop->end();
    }

    Object::PropValues& Object::operator[](std::string pName) {
      return (*prop)[pName];
    }

    std::string ObjectRoot::Key = "_ROOT";
    ObjectRoot& ObjectRoot::initialize() {
      static ObjectRoot root;
      
      return root;
    }
 
    bool ObjectRoot::exists(std::string pName) {
      return table->exists(pName);
    }

    Object& ObjectRoot::operator[](std::string pName) {
      Object::PropValues& vList = (*table)[pName];
      Object *obj = (vList.begin())->get<Object *>();
      return *obj;
    }

    Object& ObjectRoot::create(std::string name, std::string kind) {
      assert(!table->exists(name) && "unique Object name required");
      Object::PropValues& vList = (*table)[name];
      Object::Value obj = new Object(name, kind);
      vList.insert(vList.end(),obj);
      return *(obj.get<Object *>());
    }

    Object& ObjectRoot::getOrCreate(std::string name, std::string kind) {
      return table->exists(name) ? (*this)[name] : create(name, kind);
    }


  }
}
