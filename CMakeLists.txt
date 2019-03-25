project(BlpNoDebugDlg)

add_library(blp_no_debug_dlg_lib
    blp_no_debug_dlg.c
    include/blp_no_debug_dlg.h
  )
target_include_directories( blp_no_debug_dlg_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
