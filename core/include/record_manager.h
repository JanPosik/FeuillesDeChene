#ifndef RECORD_MANAGER_H
#define RECORD_MANAGER_H

#include "game_state.h"
#include "record.h"

// prepared for records from other modes
// now available only 'classic', marked as 'Default'
// record struct is located here: ./record.h

namespace Core {

	Record MakeRecord(GameState&);
	void ApplyRecord(GameState&, const Record&);

}

#endif
