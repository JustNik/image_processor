//Для проекта установлен жесткий дедлайн 23:59 30.10.2023 - это означает, что решения,
//отправленные после этого времени, не будут оцениваться.
// Created by justnik on 29.10.2023.
//

#ifndef IMAGE_PROCESSOR_PIXEL_H
#define IMAGE_PROCESSOR_PIXEL_H

#include <cstdint>

class Pixel {
public:
    static const int32_t NUM_OF_COLORS = 3;
    static const uint8_t MAX_COLOR_VALUE = 255;

    /// кажется, лучше сделать r g b в public чтоб было удобно с ними работать извне...
    /// есть ли смысл их делать protected и писать геттер, сеттер?
    uint8_t b_, g_, r_;

    Pixel() : b_(0), g_(0), r_(0) {}

    Pixel(uint16_t b, uint16_t g, uint16_t r) : b_(b), g_(g), r_(r) {}

    ~Pixel() {}

    void Negative();

    void GreyScale();

} __attribute__((packed));

#endif //IMAGE_PROCESSOR_PIXEL_H
