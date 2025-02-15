
message("<fmt>")

FetchContent_Declare(
    fmt
    GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
    GIT_TAG         9cf9f38eded63e5e0fb95cd536ba51be601d7fa2
    OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(fmt)

message("</fmt>")
