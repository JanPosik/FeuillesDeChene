#include "record_manager.h"

namespace Core {

	Record MakeRecord(GameState& state)
	{
		return {state.Record};
	}

	void ApplyRecord(GameState& state, const Record& record)
	{
		state.LastRecord = record.Default;
		state.Record = record.Default;
	}

}
