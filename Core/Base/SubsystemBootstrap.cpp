#include "SubsystemBootstrap.hpp"

namespace Core {

	SubsystemBootstrap::SubsystemBootstrap() : StartupList(0) {

		// Conservative prediction.
		StartupList = new Crude::List<Subsystem*>(5);

	}

	SubsystemBootstrap::~SubsystemBootstrap() {

		// Do not delete nonexistent data
		if (StartupList) {

			delete StartupList;

		}

	}

	void SubsystemBootstrap::RegisterSubsystem(Subsystem* TargetSubsystem) {

		// Do not add nonexistent data
		if (TargetSubsystem != 0) {

			StartupList->Insert(TargetSubsystem);

		}

	}

	bool SubsystemBootstrap::Boot() {

		Crude::List<Subsystem*> SortedNodes(5);
		Crude::List<Subsystem*> LimboNodes(5);

		// Find all nodes with no dependencies
		for (unsigned int i = 0; i < StartupList->Size(); i++) {

			if (StartupList->At(i)->getDependencyList().Size() == 0) {

				SortedNodes.Insert(StartupList->At(i));

				StartupList->Remove(i);

				i--;
			}

		}

		// Sort nodes by priority
		Sort(SortedNodes);

		while (StartupList->Size() > 0) {

			// Find all nodes that dependencies are in the 'SortedNodes' list
			for (unsigned int i = 0; i < StartupList->Size(); i++) {

				// Toggle to indicate if the current node is able to startup
				bool NodeCompatable = true;

				// List of the nodes dependencies that we require to flag the node and perform a startup
				Crude::List<Crude::String> NodeDependencies = StartupList->At(i)->getDependencyList();

				// Loop through the dependencies
				for (unsigned int j = 0; j < NodeDependencies.Size(); j++) {

					// Toggle to see if the current dependencie exists in the SortedNodes list
					bool DependencyExists = false;

					// Loop through the SortedNodes list
					for(unsigned int k = 0; k < SortedNodes.Size(); k++) {

						// Is this our dependencie stop looking and flag it as found.
						if (NodeDependencies.At(i) == SortedNodes.At(k)->GetSubsystemName()) {
							DependencyExists = true;
							break;
						}

					}

					// If one of the dependencies was not found then flag the subsystem as unable to start
					if (DependencyExists == false) {
						NodeCompatable = false;
						break;
					}

				}

				// If the node was compatible add it to this rounds list and sort (this limbo list is so that when we sort we do not mix dependencies around)
				if (NodeCompatable) {
					LimboNodes.Insert(StartupList->At(i));
					StartupList->Remove(i); // Remember to remove it from the startup list
					i--;
				}

			}

			if (LimboNodes.Size() == 0) {
				// Report error in subsystem dependencies such as a dependency starvation.
				return false;
			} else {
				// Round complete, sort the limbo list and append to the SortedNodes list.
				Sort(LimboNodes);
				for (unsigned int l = 0; l < LimboNodes.Size(); l++)
					SortedNodes.Insert(LimboNodes.At(l));

				LimboNodes.Clear();
			}

			// Next Round!
		}

		delete StartupList;
		StartupList = new Crude::List<Subsystem*>(SortedNodes);

		for (unsigned int i = 0; i < StartupList->Size(); i++) {

			StartupList->At(i)->Startup();

		}

		return true;

	}

	bool SubsystemBootstrap::Kill() {

		// Shutdown in reverse order
		for (int i = StartupList->Size(); i > 0; i--) {

			StartupList->At(i-1)->Shutdown();

		}

		return true;

	}

	void SubsystemBootstrap::Sort(Crude::List<Subsystem*>& TargetList) {


		bool Sorted = false;
		bool Breaking = false;

		while (!Sorted) {

			for (unsigned int i = 0; i < TargetList.Size(); i++) {

				for (unsigned int j = 0; j < TargetList.Size(); j++) {

					if (TargetList.At(i)->GetPriority() < TargetList.At(j)->GetPriority()) {
					
						TargetList.Swap(i,j);
						Breaking = true;
						break;
					
					}

				}

				if (Breaking)
					break;
			}

			if (!Breaking) {
				Breaking = false;
				Sorted = true;
				break;
			}

		}

	}

}