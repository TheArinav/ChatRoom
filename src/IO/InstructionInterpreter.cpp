#include "InstructionInterpreter.h"
#include <iostream>

using namespace IO::InstructionInterpreter;
namespace IO {

    void InstructionInterpreter::Setup() {
        vector<string> list = {
                "-1:h/help|general,server,client",
                "-1:q/exit|",
                "-1:scx/show-context|",
                "-1:ecx/exit-context|",
                "0:s/start|server,client",
                "1:sd/shutdown|",
                "1:bc/broadcast|-msg %s/--message %s",
                "3:ccr/change-chat-room|-id %i/--roomID %i,-n %s/--roomName %s",
                "3:msgin/messageIn|-i %i/--roomID %i,-name %s/--roomName %s|-mc %s/--messageContent %s",
                "5:msg/message|-mc %s/--messageContent %s",
                "2:li/login|-id %i",
                "3:lo/logout|",
                "2:mcr/make-chat-room|-n %s/--name %s|-i %i[]/--clientIDs %i[]",
                "4:rcr/rename-chat-room|-nn %s/-newName %s",
                "4:kcr/kill-chat-room|-i %i/-roomID %i",
                "5:prm/promote-member|-i %i/--clientID %i",
                "5:dem/demote-member|-i %i/--clientID %i",
                "4:ler/leave-room|-i %i/--roomID %i,-n %s/--roomName %s",
                "5:kr/kick-from-room|-i %i{,}/--clientIDs %i{,}",
                "2:reg/register|-sa %i/--serverAddress %i|-cdn %s/--clientDisplayName %s",
                "2:accnts/accounts|",
                "2:ra/remove-account|",
                "4:sf/save-friend|-i %i/--clientID %i",
                "4:delf/delete-friend|-i %o/--clientID %i",
                "3:pfl/print-friend-list|"
        };

        for (const string &cur: list) {
            InstructionType toPush = ProcessInstruction(cur);
            if (toPush.LongForm.empty())
                std::cerr << "Parse of: '" << cur << "' has failed!" << "\n";
            else
                InstTypes.push_back(toPush);
        }
    }

    static InstructionType InstructionInterpreter::ProcessInstruction(const string &inp) {
        int i, j;
        bool stop = false;
        InstructionType res = {};

        //region GetContext
        {
            for (i = 0; i < inp.size() && !stop; stop = inp[i++] == ':');
            if (!stop)
                return {};
            int contID = std::stoi(inp.substr(0, i - 1));
            if (!(contID > -2 && contID < 6))
                return {};
            res.ValidContext = static_cast<Context>(contID);
        }
        //endregion


        //region GetForms
        {
            stop = false;
            j = i;
            for (; i < inp.size() && !stop; stop = inp[i++] == '|');
            if (!stop)
                return {};
            string names = inp.substr(j, i - j - 1);

            //Split names:
            stop = false;
            for (j = 0; j < names.size() && !stop; stop = names[j++] == '/');
            if (!stop)
                return {};
            res.ShortForm = names.substr(0, j - 1);
            res.LongForm = names.substr(j);
        }
        //endregion

        //Exit if instruction requires no parameters
        if (inp.size() == i)
            return res;

        //region Params
        {
            string paramSpace = inp.substr(i, inp.size() - i);
            //region SeparateCategories
            vector<string> categories;
            stop = false;
            string current = string(paramSpace);
            do {
                stop = false;
                for (i = 0; i < current.size() && !stop; stop = current[i++] == '|');
                categories.push_back(current.substr(0, (stop) ? i - 1 : i));
                current = current.substr(i);
            } while (stop);
            //endregion
            j = 0;
            for (const string &cat: categories) {
                //region SeparateParams
                vector<string> params;
                stop = false;
                current = string(cat);
                do {
                    stop = false;
                    for (i = 0; i < current.size() && !stop; stop = current[i++] == ',');
                    params.push_back(current.substr(0, (stop) ? i - 1 : i));
                    current = current.substr(i);
                } while (stop);
                //endregion

                for (const string &param: params) {
                    //Search for '-'
                    stop = false;
                    for (i = 0; i < param.size() && !stop; stop = param[i++] == '-');
                    ParameterType cur;
                    if (!stop) {
                        cur.TypeDescriptor = "static";
                        cur.LongForm = string(param);
                        cur.ShortForm = string(param);
                    } else {
                        stop = false;
                        for (i = 0; i < param.size() && !stop; stop = param[i++] == '/');
                        string sSec = param.substr(0, i - 1);
                        string lSec = param.substr(i);

                        stop = false;
                        for (i = 0; i < sSec.size() && !stop; stop = sSec[i++] == ' ');
                        cur.ShortForm = string(sSec.substr(0, i - 1));

                        cur.TypeDescriptor = string(sSec.substr(i));

                        stop = false;
                        for (i = 0; i < lSec.size() && !stop; stop = lSec[i++] == ' ');
                        cur.LongForm = lSec.substr(0, i - 1);
                    }

                    cur.CategoryIndex = j;

                    stop = false;
                    for (i = 0; i < ParamTypes.size() && !stop; stop = ParamTypes[i++].ShortForm == cur.ShortForm);
                    if (!stop) {
                        ParamTypes.push_back(cur);
                        i = (int) ParamTypes.size();
                    }
                    res.Parameters.push_back(ParamTypes[i - 1]);
                }
                j++;
            }
        }
        //endregion

        return res;
    }

    Instruction InstructionInterpreter::Parse(const string &inp) {
        string checkRes = IsLegalInst(inp);
        if (!checkRes.empty())
            throw std::invalid_argument(checkRes);

        Instruction res = {};

        return res;
    }

    static string InstructionInterpreter::IsLegalInst(const string &inp) {
        string instName;
        int i, j;
        bool stop = false;

        //Get instruction name
        for (i = 0; i < inp.size() && !stop; stop = inp[i++] == ' ');
        instName = inp.substr(0, (stop)?i-1:i);

        //region GetInstructionType
        stop = false;
        for (i = 0; i < InstTypes.size() && !stop; stop = (InstTypes[i].ShortForm == instName ||
                                                           InstTypes[i].LongForm == instName), i++);
        if(!stop)
            return "Unknown instruction '" + instName + "'";

        InstructionType &instType = InstTypes[i-1];
        //endregion

        if(instType.Parameters.size()>1 && instType.Parameters[0].TypeDescriptor == "static"){
            string param;
            stop=false;
            for (i = 0; i < inp.size() && !stop; stop = inp[i++] == ' ');
            param = inp.substr(i);
            stop=false;
            for(const auto& sParam:instType.Parameters)
                if((stop=sParam.ShortForm==param))
                    break;
            if(!stop)
                return "Invalid static parameter '" + param + "' for instruction '" +instName + "'";
        }else if (!instType.Parameters.empty()){

        }
        return "";
    }


}
