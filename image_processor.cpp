#include "bmp_utils.h"
#include "cmd_parser.h"
#include "converter.h"
#include "filter.h"
#include <cassert>
#include <iostream>

const std::string FLAG_PATH = "C:/hw/cpp/pmi-235-2-Nikita-Greben-JustNik77/tasks/image_processor/test_script/data/flag.bmp";
const std::string TMP_OUTPUT = "../output.bmp";
//const std::string LENNA_PATH = ""

void Test01() {
    BMPReaderWriter bmp_rw;
    bmp_rw.Open(FLAG_PATH);
    assert(bmp_rw.IsOpen());
}

void Test02() {
    BMPReaderWriter bmp_rw;
    bmp_rw.ReadBMP(FLAG_PATH);
}

void Test03() {
    BMPReaderWriter bmp_rw;
    bmp_rw.ReadBMP(FLAG_PATH);
    Image *img = bmp_rw.ReadImage();
    delete img;
}

void Test04() {
    BMPReaderWriter bmp_rw;
    bmp_rw.ReadBMP(FLAG_PATH);
    Image *img = bmp_rw.ReadImage();
    Filter *filter = new Crop();

    filter->SetParams({"10", "10"});
    filter->Apply(img);

    delete filter;
    filter = new GreyScale();
    filter->Apply(img);

    bmp_rw.WriteBMP(img, TMP_OUTPUT);
    assert(img->GetWidth() == 10 && img->GetHeight() == 10);
}

int main(int argc, char **argv) {
    try {
        Test01();
        Test02();
        Test03();
//        Test04();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Unknown exception." << "\n";
        return -1;
    }
    std::cout << "All tests passed\n";


    CMDLineParser parser(argc, argv);
    std::vector<FilterParameters> filters = parser.GetFilters();

    BMPReaderWriter bmp_rw;
    bmp_rw.ReadBMP(parser.GetInputFilePath());

    Image *img = bmp_rw.ReadImage();

    Converter converter(filters);
    Pipeline pipeline = converter.GetPipeline();

    pipeline.Apply(img);

    bmp_rw.WriteBMP(img, parser.GetOutputFilePath());

    return 0;
}
