#include "Path.h"

namespace Crude {

	Path::Path() {
	}

	Path::Path(Crude::String PathName) : m_Data(PathName) {
		Format();
	}

	Path::Path(const char* PathName) : m_Data(PathName) {
		Format();
	}

	Crude::String Path::GetData() {
		return m_Data;
	}

	void Path::Format() {
		while(m_Data[0] == '.' || m_Data[0] == '\\' || m_Data[0] == '/') {
			m_Data.nRemove('.', 1);
			m_Data.nRemove('\\', 1);
			m_Data.nRemove('/', 1);
		}
	}

	Path::~Path() {
	}

}