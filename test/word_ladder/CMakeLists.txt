configure_file("english.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("Empty.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("SingleLetterWordsPath.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("MultipleHopsFailure.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("ZeroHopsFailure.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("OnePathSuccess.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("NoLoops.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("BasicMultiplePathsSuccess.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("MultiplesPathsWithDoubleUps.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("BasicEmbeddedDubUps.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("ComplexCollidingPaths.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

cxx_test(
   TARGET basic_tests
   FILENAME basic_tests.cpp
   LINK word_ladder lexicon test_main
)

cxx_test(
   TARGET multiple_path_tests
   FILENAME multiple_path_tests.cpp
   LINK word_ladder lexicon test_main
)

cxx_test(
   TARGET tests_using_english_lexicon
   FILENAME tests_using_english_lexicon.cpp
   LINK word_ladder lexicon test_main
)

cxx_test(
   TARGET word_ladder_test_benchmark
   FILENAME word_ladder_test_benchmark.cpp
   LINK word_ladder lexicon test_main
)
