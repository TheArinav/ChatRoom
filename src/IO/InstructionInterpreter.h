#ifndef INSTRUCTION_INTERPRETER_H
#define INSTRUCTION_INTERPRETER_H

#include <vector>
#include <string>
#include <sstream>
#include <any>

using std::string;
using std::vector;
using std::any;

namespace IO {
    enum class Context {
        ANY=-1,
        NONE=0,
        SERVER=1,
        CLIENT_LOGGED_OUT=2,
        CLIENT_LOGGED_IN=3,
        CLIENT_LOGGED_IN_NO_ROOM=4,
        CLIENT_LOGGED_IN_ROOM=5
    };
    struct ParameterType{
        string ShortForm;
        string LongForm;
        string TypeDescriptor;
        int CategoryIndex;
    };
    struct InstructionType{
        string ShortForm;
        string LongForm;
        Context ValidContext;
        vector<ParameterType> Parameters;
    };
    struct Parameter{
        ParameterType *Type;
        any Value;
    };
    struct Instruction{
        InstructionType *Type;
        vector<Parameter> Params;
    };
    namespace InstructionInterpreter{
        static vector<ParameterType> ParamTypes;
        static vector<InstructionType> InstTypes;
        void Setup();
        Instruction Parse(const string&);
        static InstructionType ProcessInstruction(const string &inp);

    }
}

#endif