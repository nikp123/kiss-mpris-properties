find_package(PkgConfig)

pkg_check_modules(DBUS REQUIRED dbus-1)

add_library(kiss-mpris kiss-mpris.c)
target_link_libraries(kiss-mpris      PRIVATE "${DBUS_LIBRARIES}")
target_link_directories(kiss-mpris    PRIVATE "${DBUS_LIBRARY_DIRS}")
target_include_directories(kiss-mpris PRIVATE "${DBUS_INCLUDE_DIRS}")

install(TARGETS kiss-mpris DESTINATION lib)
install(FILES kiss-mpris.h DESTINATION include)

