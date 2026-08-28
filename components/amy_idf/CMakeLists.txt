set(AMY_DIR ${CMAKE_CURRENT_LIST_DIR}/../amy)

idf_component_register(
    SRCS
        "${AMY_DIR}/src/algorithms.c"
        "${AMY_DIR}/src/amy.c"
        "${AMY_DIR}/src/api.c"
        "${AMY_DIR}/src/cv_trigger.c"
        "${AMY_DIR}/src/custom.c"
        "${AMY_DIR}/src/delay.c"
        "${AMY_DIR}/src/envelope.c"
        "${AMY_DIR}/src/examples.c"
        "${AMY_DIR}/src/filters.c"
        "${AMY_DIR}/src/i2s.c"
        "${AMY_DIR}/src/instrument.c"
        "${AMY_DIR}/src/interp_partials.c"
        "${AMY_DIR}/src/log2_exp2.c"
        "${AMY_DIR}/src/midi_mappings.c"
        "${AMY_DIR}/src/oscillators.c"
        "${AMY_DIR}/src/parse.c"
        "${AMY_DIR}/src/patches.c"
        "${AMY_DIR}/src/pcm.c"
        "${AMY_DIR}/src/sequencer.c"
        "${AMY_DIR}/src/transfer.c"
        "${AMY_DIR}/src/amy_midi.c"
    INCLUDE_DIRS "${AMY_DIR}/src"
    REQUIRES esp_driver_i2s esp_driver_uart esp_timer
)

target_compile_definitions(${COMPONENT_LIB} PRIVATE AMY_WAVETABLE AMY_NO_MINIAUDIO)
target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-incompatible-pointer-types)
