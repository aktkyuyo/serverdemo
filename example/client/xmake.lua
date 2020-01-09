target("client")
    -- add_deps("socket_io")
    set_kind("binary")
    add_files("*.cpp")
    if is_os("windows") then
        add_files("$(projectdir)/lib/win/*.lib")
    else
        add_files("$(projectdir)/lib/linux/*.a")
    end