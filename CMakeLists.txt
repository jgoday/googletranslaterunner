project(googletranslate)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include(MacroLibrary)
include(MacroOptionalDependPackage)

find_package(KDE4Workspace REQUIRED)
find_package(KdepimLibs REQUIRED)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories (${KDE4_INCLUDES}
                     ${KDE4WORKSPACE_INCLUDE_DIR}
                     ${KDEPIMLIBS_INCLUDE_DIR}
                     ${CMAKE_CURRENT_SOURCE_DIR}/libs)


set(krunner_googletranslate_SRCS
    googletranslate.cpp
    googletranslatehttp.cpp
    googletranslateutil.cpp
)

set(kcm_krunner_googletranslate_SRCS
    googletranslate_config.cpp
)

kde4_add_ui_files(kcm_krunner_googletranslate_SRCS googletranslate_config.ui)
kde4_add_plugin(kcm_krunner_googletranslate ${kcm_krunner_googletranslate_SRCS})
target_link_libraries(kcm_krunner_googletranslate
    ${KDE4_KDECORE_LIBS}
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KUTILS_LIBS}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    )

kde4_add_plugin(krunner_googletranslate ${krunner_googletranslate_SRCS})
target_link_libraries(krunner_googletranslate ${KDE4_KUTILS_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_PLASMA_LIBS} ${KDE4_KIO_LIBS})

install(TARGETS krunner_googletranslate kcm_krunner_googletranslate DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-runner-googletranslate.desktop plasma-runner-googletranslate_config.desktop DESTINATION ${SERVICES_INSTALL_DIR})

