#ifndef CLI_RECORD_MANAGER_H
#define CLI_RECORD_MANAGER_H

#include "record.h"

namespace CLI {

	class RecordManager {

		public:
			Core::Record Load();
			void Save(const Core::Record&, bool);
	};

}

#endif
