#include "Standard.h"

// Methods for handling crashes that occur during the application's execution.
// These stubs are placeholders. Implementing meaningful pre-crash and 
// fatal error handling will improve robustness.
void preCrash()
{
}

void onFatalError(g3::FatalMessagePtr fatal_message)
{
}

int ActivateGeneric(long version, GlobalFunc* global, LWLayoutGeneric* local, void* serverData)
{
	// Checks if the plugin version matches the expected version.
	if (version != LWLAYOUTGENERIC_VERSION)
		return AFUNC_BADVERSION;

	// Initializes a log handler with crash handling functions.
	LogHandler log(onFatalError, preCrash);

	LWMessageFuncs* const msgFuncs = (LWMessageFuncs*)global(LWMESSAGEFUNCS_GLOBAL, GFUSE_TRANSIENT);
	// Checks if the message functions are valid.
	if (!msgFuncs) return AFUNC_BADGLOBAL;

	// Displays an information message in LightWave.
	msgFuncs->info("SimpleGenericPlugin executed", nullptr);

	// Logs a debug message.
	LOG(DBUG) << "SimpleGenericPlugin executed";

	// Evaluates a command in LightWave, in this case, showing an about dialog.
	local->evaluate(local->data, "About");

	return AFUNC_OK;
}
