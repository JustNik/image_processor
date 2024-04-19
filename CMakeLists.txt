add_executable(
    image_processor
    image_processor.cpp
        bmp_utils.cpp bmp_utils.h filter.cpp filter.h image.cpp image.h pixel.cpp pixel.h cmd_parser.cpp cmd_parser.h converter.cpp converter.h filters_pipeline.cpp filters_pipeline.h)
