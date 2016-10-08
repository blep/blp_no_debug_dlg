#include "blp_no_debug_dlg.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(_MSC_VER)
/* Used to install a report hook that prevent dialog on assertion and error. */
# include <crtdbg.h>
#endif /* #if defined(_MSC_VER) */

#if defined(_WIN32)
/* Used to prevent dialog on memory fault. */
/* Limits headers included by Windows.h */
# define WIN32_LEAN_AND_MEAN
# define NOSERVICE
# define NOMCX
# define NOIME
# define NOSOUND
# define NOCOMM
# define NORPC
# define NOGDI
# define NOUSER
# define NODRIVERS
# define NOLOGERROR
# define NOPROFILER
# define NOMEMMGR
# define NOLFILEIO
# define NOOPENFILE
# define NORESOURCE
# define NOATOM
# define NOLANGUAGE
# define NOLSTRING
# define NODBCS
# define NOKEYBOARDINFO
# define NOGDICAPMASKS
# define NOCOLOR
# define NOGDIOBJ
# define NODRAWTEXT
# define NOTEXTMETRIC
# define NOSCALABLEFONT
# define NOBITMAP
# define NORASTEROPS
# define NOMETAFILE
# define NOSYSMETRICS
# define NOSYSTEMPARAMSINFO
# define NOMSG
# define NOWINSTYLES
# define NOWINOFFSETS
# define NOSHOWWINDOW
# define NODEFERWINDOWPOS
# define NOVIRTUALKEYCODES
# define NOKEYSTATES
# define NOWH
# define NOMENUS
# define NOSCROLL
# define NOCLIPBOARD
# define NOICONS
# define NOMB
# define NOSYSCOMMANDS
# define NOMDI
# define NOCTLMGR
# define NOWINMESSAGES
# include <windows.h>
#endif /* #if defined(_WIN32) */


#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
    /* Hook MSVCRT assertions to prevent dialog from appearing */
    static int msvcrtSilentReportHook( int reportType, char *message, int *returnValue )
    {
        (void)(returnValue); /* silent unused warning */
        // The default CRT handling of error and assertion is to display
        // an error dialog to the user.
        // Instead, when an error or an assertion occurs, we force the 
        // application to terminate using abort() after display
        // the message on stderr. 
        if ( reportType == _CRT_ERROR
             ||  reportType == _CRT_ASSERT )
        {
            // calling abort() cause the ReportHook to be called
            // The following is used to detect this case and let's the
            // error handler fallback on its default behaviour (
            // display a warning message)
            static volatile int isAborting = 0;
            if ( isAborting != 0 ) 
            {
                return TRUE;
            }
            isAborting = 1;

            fprintf( stderr, "CRT Error/Assert:\n%s\n", message );
            fflush( stderr );
            abort();
        }
        // Let's other reportType (_CRT_WARNING) be handled as they would by default
        return FALSE;
    }
#endif /* #if defined(_MSC_VER) */


void blp_no_debug_dlg(void)
{
#if defined(_MSC_VER)
    /* Install a hook to prevent MSVCRT error and assertion from
     * popping a dialog.
     */
    _CrtSetReportHook( &msvcrtSilentReportHook );
#endif /* #if defined(_MSC_VER) */

    /* @todo investiguate this handler (for buffer overflow)
     * _set_security_error_handler
     */

#if defined(_WIN32)
    /* Prevents the system from popping a dialog for debugging if the
     * application fails due to invalid memory access.
     * (Windows Error Dialog)
     */
    SetErrorMode( SEM_FAILCRITICALERRORS 
                  | SEM_NOGPFAULTERRORBOX 
                  | SEM_NOOPENFILEERRORBOX );
#endif /* if defined(_WIN32) */
}


void blp_no_debug_dlg_unless_debugging(void)
{
#if defined(_WIN32)
    /* If someone is debugger, let's all issues be handled by the debugger */
    if ( IsDebuggerPresent() )  
        return;
#endif
    blp_no_debug_dlg();
}

#ifdef __cplusplus
} /* extern "C" { */
#endif
