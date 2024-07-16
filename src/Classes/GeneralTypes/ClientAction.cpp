#include "ClientAction.h"
#include <string>
#include <sstream>
#include <utility>

using std::stringstream;
using std::string;
using std::istringstream;
using std::move;

namespace GeneralTypes {
    ClientAction::ClientAction():
    Type(ClientActionType::InformFailure),Data(), RecipientAddress(){}

    ClientAction::ClientAction(ClientActionType type, const string& data, sockaddr_in addr) :
    Type(type),Data(data), RecipientAddress(addr){}

    string ClientAction::ToString() {
        stringstream ss;
        ss << "ClientAction: {"
        << "\n\tType: " << static_cast<int>(Type)
        << "\n\tData: " << (string)Data
        << "\n\tRecipientAddress: " << RecipientAddress.sin_addr.s_addr
        << "\n}";
        return ss.str();
    }

    string ClientAction::Serialize() {
        stringstream ss;
        ss << static_cast<int>(Type) << " "
        << RecipientAddress.sin_addr.s_addr << " "
        << RecipientAddress.sin_port << " "
        << RecipientAddress.sin_zero << " "
        << RecipientAddress.sin_family << " "
        << (string)Data;
        return ss.str();
    }

    ClientAction ClientAction::Deserialize(const string& inp) {
        istringstream iss(inp);
        ClientAction res;
        int type;
        sockaddr_in addr={};

        string data;
        iss >> type
        >> addr.sin_addr.s_addr
        >> addr.sin_port
        >> addr.sin_zero
        >> addr.sin_family
        >> data;

        res.Type=static_cast<ClientActionType>(type);
        res.RecipientAddress=addr;
        res.Data+=data;

        return res;
    }
} // GeneralTypes