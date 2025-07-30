idf_component_register(
    SRCS "main.c" "mic.c"
    INCLUDE_DIRS "." "../../include" "../../test"
    REQUIRES driver
)
