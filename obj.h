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


#ifndef __GUARD_OBJ_H
#define __GUARD_OBJ_H

#include <limits>
#include <list>
#include <string>
#include <set>
#include <map>
#include "llvm/ADT/PointerUnion.h"

namespace ToolScribe {

  namespace ODD {

    class Object {
    public:

      // Object implements a dictionary of property values to define
      // the Object data model. Property values are a container class
      // whose members are pointers to any of "std::string", "long",
      // "double", or "Object". NAME and KIND are predefined keys whose
      // values are a string recording the name and kind of (*this)

      // Each element of the property container is an instance of an
      // LLVM PointerUnion, and that interface should be used to
      // manipulate the container element values.

      // The property value container class is exposed by reference.
      // Use the standard container protocol to manipulate the content.

      typedef llvm::PointerUnion4<std::string *, long *, double *, Object *> Value;
      typedef std::list<Value> PropValues;
      typedef std::set<std::string> PropKeys;
      static std::string nameKey;
      static std::string kindKey;

    private:
      typedef std::map<std::string, PropValues> Dictionary;
      static std::string refKey;

      Object::Dictionary *prop;

    public:
      Object(std::string name, std::string kind);
      Object(Object&);
      Object& operator=(Object&);
      ~Object();

      PropKeys& keys();
      bool exists(std::string);
      PropValues& operator[](std::string);
    };

    class ObjectRoot {
    private:
      static std::string Key;

      Object *table;
      ObjectRoot() { table = new Object(ObjectRoot::Key, ObjectRoot::Key); }
      ObjectRoot(ObjectRoot const &);
      void operator=(ObjectRoot const &);
    public:
      static ObjectRoot& initialize();
      bool exists(std::string);
      Object& operator[](std::string);
      Object& create(std::string, std::string);
      Object& getOrCreate(std::string, std::string);
    };

  }

}

#endif
