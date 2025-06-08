FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.1
)

FetchContent_MakeAvailable(spdlog)

if(TARGET spdlog)
    include(GNUInstallDirs)
    install(TARGETS spdlog
        EXPORT spdlogTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    install(EXPORT spdlogTargets
        FILE spdlogTargets.cmake
        NAMESPACE spdlog::
        DESTINATION lib/cmake/spdlog
    )
endif()