#include "Configuration.h"

namespace Core {

	Crude::List<Crude::String> Configuration::getDependencyList() {
		Crude::List<Crude::String> ReturnList(2);
		ReturnList.Insert("FileSystem");
		return ReturnList;
	}

	bool Configuration::Startup() {
		UpdateMessage.MessageType = MSG_CONFIG_UPDATED;
		return true;
	}

	void Configuration::Shutdown() {
	}

	bool Configuration::Poll() {
		return true;
	}

	void Configuration::PullMessages(Crude::Que<Core::Message>& Messages) {
		if (this->Messages.Size() != 0) {
			while(Message* CurrentMessage = this->Messages.Pop()) {
				Messages.Push(CurrentMessage);
			}
		}
	}

	void Configuration::ProcessMessage(Crude::Que<Core::Message> Messages) {
	}

	void Configuration::onSystemDown(Subsystem& TargetSystem) {
	}

	void Configuration::onSystemUp(Subsystem& TargetSystem) {
	}

}