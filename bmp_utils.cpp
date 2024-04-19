#include "bmp_utils.h"
#include <iostream>

void BMPReaderWriter::Open(const std::string &filename) {
    if (filename.empty()) {
        throw std::invalid_argument("Filename is invalid.");
    }
    file_.open(filename, std::ios::in | std::ios::binary);
    if (!file_.is_open()) {
        throw std::runtime_error("Cannot open file.");
    }
    filename_ = filename;
}

void BMPReaderWriter::Close() {
    file_.close();
    filename_.clear();
}

BMPReaderWriter::~BMPReaderWriter() {
    Close();
}

bool BMPReaderWriter::IsOpen() {
    return file_.is_open();
}

void BMPReaderWriter::ReadBMP(const std::string &filename) {
    Open(filename);

    if (!IsOpen()) {
        throw std::logic_error("File is not open.");
    }
    /// always read from the beginning
    file_.seekg(0);

    ReadBMPHeader();
    ReadDIBHeader();
}

void BMPReaderWriter::ReadBMPHeader() {
    if (file_.tellg() != 0) {
        throw std::runtime_error("Invalid stream position while reading BMP header.");
    }

    file_.read(reinterpret_cast<char *>(&bmp_header_), sizeof(BMPHeader));

    if (bmp_header_.signature != BMP_SIGNATURE) {
        throw std::runtime_error("Invalid BMP signature.");
    }
}

void BMPReaderWriter::ReadDIBHeader() {
    if (file_.tellg() != sizeof(BMPHeader)) {
        throw std::runtime_error("Invalid stream position while reading DIB header.");
    }

    file_.read(reinterpret_cast<char *>(&bmp_dib_header_), sizeof(DIBHeader));

    if (bmp_dib_header_.header_size != DIB_HEADER_SIZE) {
        throw std::runtime_error("Invalid DIB header file_size.");
    }

    bytes_per_row_ = GetImageWidth() * Pixel::NUM_OF_COLORS;
    /// ceil number cause it should be divisible by 4
    bytes_per_row_ = (bytes_per_row_ + BYTES_PER_INT - 1) / BYTES_PER_INT * BYTES_PER_INT;
}

Image *BMPReaderWriter::ReadImage() {
    if (file_.tellg() != sizeof(BMPHeader) + sizeof(DIBHeader)) {
        throw std::runtime_error("Invalid stream position.");
    }
    Image *image = new Image(bmp_dib_header_.width, bmp_dib_header_.height);

    int64_t diff = bytes_per_row_ - GetImageWidth() * Pixel::NUM_OF_COLORS;

    for (int32_t i = 0; i < GetImageHeight(); ++i) {
        file_.read(reinterpret_cast<char *>(image->GetImageRow(i)),
                   static_cast<int32_t>(sizeof(Pixel)) * GetImageWidth());
        file_.seekg(diff, std::ios::cur);
    }
    return image;
}

int32_t BMPReaderWriter::GetImageWidth() const {
    return bmp_dib_header_.width;
}

int32_t BMPReaderWriter::GetImageHeight() const {
    return bmp_dib_header_.height;
}

void BMPReaderWriter::SetDefaultBMPHeader() {
    bmp_header_.signature = BMP_SIGNATURE;
    bmp_header_.file_size = HEADER_SIZE + DIB_HEADER_SIZE + GetImageHeight() * bytes_per_row_;
    bmp_header_.reserved1 = 0x00;
    bmp_header_.reserved2 = 0x00;
    bmp_header_.offset = DEFAULT_OFFSET;
}

void BMPReaderWriter::SetDefaultDIBHeader(uint32_t width, uint32_t height) {
    bmp_dib_header_.header_size = DIB_HEADER_SIZE;
    bmp_dib_header_.width = static_cast<int32_t>(width);
    bmp_dib_header_.height = static_cast<int32_t>(height);
    bmp_dib_header_.color_planes_num = 1;
    bmp_dib_header_.bits_per_pixel = BITS_PER_PIXEL;
    bmp_dib_header_.compression = 0x00;
    bmp_dib_header_.img_size = 0x00;
    bmp_dib_header_.hor_res = 0x00;
    bmp_dib_header_.ver_res = 0x00;
    bmp_dib_header_.colors_num = 0x00;
    bmp_dib_header_.important_colors_num = 0x00;
    bytes_per_row_ = GetImageWidth() * Pixel::NUM_OF_COLORS;
    /// ceil number cause it should be divisible by 4
    bytes_per_row_ = (bytes_per_row_ + BYTES_PER_INT - 1) / BYTES_PER_INT * BYTES_PER_INT;
}

void BMPReaderWriter::WriteBMP(Image *img, std::string output_filename) {
    if (IsOpen()) {
        Close();
    }
    /// strictly in this order
    SetDefaultDIBHeader(img->GetWidth(), img->GetHeight());
    SetDefaultBMPHeader();

    SetFileName(output_filename);

    file_.open(output_filename, std::ios::binary | std::ios::out | std::ios::trunc); // trunc to delete content in file
    if (!file_.is_open()) {
        throw std::runtime_error("Cannot open file.");
    }

    file_.seekp(0);
    file_.write(reinterpret_cast<char *>(&bmp_header_), sizeof(BMPHeader));

    if (file_.tellp() != sizeof(BMPHeader)) {
        throw std::runtime_error("Invalid stream position.");
    }

    file_.write(reinterpret_cast<char *>(&bmp_dib_header_), sizeof(DIBHeader));

    if (file_.tellp() != sizeof(BMPHeader) + sizeof(DIBHeader)) {
        throw std::runtime_error("Invalid stream position.");
    }

    int64_t diff = bytes_per_row_ - GetImageWidth() * Pixel::NUM_OF_COLORS;
    for (int32_t i = 0; i < GetImageHeight(); ++i) {
        file_.write(reinterpret_cast<char *>(img->GetImageRow(i)),
                   static_cast<int32_t>(sizeof(Pixel)) * GetImageWidth());
        file_.seekg(diff, std::ios::cur);
    }
    Close();
}
