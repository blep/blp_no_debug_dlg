#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Disable Windows Error Dialog and Visual Studio assertion/abort dialog.
     *
     * On assertion, message is printed to stderr before calling abort().
     */
    void blp_no_debug_dlg(void);
    
    /**
     * Call blp_no_debug_dlg() only if no debugger is attached.
     */
    void blp_no_debug_dlg_unless_debugging(void);

#ifdef __cplusplus
} /* extern "C" { */
#endif
