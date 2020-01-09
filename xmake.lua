add_rules("mode.debug", "mode.release")
-- add_rules("mode.release")

if is_os("windows") then
    add_defines("ASIO_STANDALONE", "BOOST_ASIO_STANDALONE", " _WIN32_WINDOWS=0x0601")
    -- add_defines("ASIO_STANDALONE", "BOOST_ASIO_STANDALONE", "_WIN32_WINNT=0x0A00")
    add_cxxflags("/EHsc", "/MTd")
    add_linkdirs("$(projectdir)/lib/win")
else
    add_defines("ASIO_STANDALONE", "BOOST_ASIO_STANDALONE")
    add_ldflags("-lpthread")
    add_linkdirs("$(projectdir)/lib/linux")
end

add_includedirs("$(projectdir)/include")

add_subdirs("src")
add_subdirs("example/client")
add_subdirs("example/server")