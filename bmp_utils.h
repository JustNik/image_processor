#ifndef IMAGE_PROCESSOR_BMP_UTILS_H
#define IMAGE_PROCESSOR_BMP_UTILS_H

#include "image.h"
#include <fstream>

class BMPReaderWriter {
public:
    static const uint64_t BMP_SIGNATURE = 0x4D42;
    static const uint32_t HEADER_SIZE = 0x0E;
    static const uint32_t DIB_HEADER_SIZE = 0x28;
    static const uint32_t DEFAULT_OFFSET = 0x36;
    static const uint8_t BITS_PER_PIXEL = 24;
    static const uint32_t BYTES_PER_INT = 4; /// я честно не знаю как иначе обрабатывать паддинги

    struct BMPHeader {
        uint16_t signature;
        uint32_t file_size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset;
    } __attribute__((packed));

    struct DIBHeader {
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t color_planes_num;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t img_size;
        int32_t hor_res;
        int32_t ver_res;
        uint32_t colors_num;
        uint32_t important_colors_num;
    } __attribute__((packed));

public:
    BMPReaderWriter() : filename_(std::string()), file_() {}

    ~BMPReaderWriter();

    void Open(const std::string &filename);

    void Close();

    bool IsOpen();

    void ReadBMP(const std::string &filename);

    Image *ReadImage();

    int32_t GetImageWidth() const;

    int32_t GetImageHeight() const;

    void SetDefaultBMPHeader();

    void SetDefaultDIBHeader(uint32_t width, uint32_t height);

    std::string GetFileName() { return filename_; }

    void SetFileName(std::string &filename) { filename_ = filename; }

    const std::string &GetFileName() const { return filename_; }

    void WriteBMP(Image *img, std::string output_filename);
protected:
    std::string filename_;
    std::fstream file_;

    uint32_t bytes_per_row_;

    BMPHeader bmp_header_;
    DIBHeader bmp_dib_header_;

    void ReadBMPHeader();

    void ReadDIBHeader();
};


#endif //IMAGE_PROCESSOR_BMP_UTILS_H
