#include <gtest/gtest.h>
#include <cmath>

#include "SeamCarver.h"

TEST(SeamCarvingTests, ImageEnergy3x4)
{
    const std::vector<Image::Pixel> col0 = { Image::Pixel(255, 101,  51), Image::Pixel(255, 153,  51), Image::Pixel(255, 203,  51), Image::Pixel(255, 255,  51) };
    const std::vector<Image::Pixel> col1 = { Image::Pixel(255, 101, 153), Image::Pixel(255, 153, 153), Image::Pixel(255, 204, 153), Image::Pixel(255, 255, 153) };
    const std::vector<Image::Pixel> col2 = { Image::Pixel(255, 101, 255), Image::Pixel(255, 153, 255), Image::Pixel(255, 205, 255), Image::Pixel(255, 255, 255) };

    const Image image({std::move(col0), std::move(col1), std::move(col2)});
    SeamCarver carver(std::move(image));

    EXPECT_DOUBLE_EQ(sqrt(20808.0), carver.GetPixelEnergy(0, 0));
    EXPECT_DOUBLE_EQ(sqrt(52020.0), carver.GetPixelEnergy(1, 0));
    EXPECT_DOUBLE_EQ(sqrt(20808.0), carver.GetPixelEnergy(2, 0));

    EXPECT_DOUBLE_EQ(sqrt(20808.0), carver.GetPixelEnergy(0, 1));
    EXPECT_DOUBLE_EQ(sqrt(52225.0), carver.GetPixelEnergy(1, 1));
    EXPECT_DOUBLE_EQ(sqrt(21220.0), carver.GetPixelEnergy(2, 1));

    EXPECT_DOUBLE_EQ(sqrt(20809.0), carver.GetPixelEnergy(0, 2));
    EXPECT_DOUBLE_EQ(sqrt(52024.0), carver.GetPixelEnergy(1, 2));
    EXPECT_DOUBLE_EQ(sqrt(20809.0), carver.GetPixelEnergy(2, 2));

    EXPECT_DOUBLE_EQ(sqrt(20808.0), carver.GetPixelEnergy(0, 3));
    EXPECT_DOUBLE_EQ(sqrt(52225.0), carver.GetPixelEnergy(1, 3));
    EXPECT_DOUBLE_EQ(sqrt(21220.0), carver.GetPixelEnergy(2, 3));
}

TEST(SeamCarvingTests, ImageVerticalSeam3x4)
{
    const std::vector<Image::Pixel> col0 = { Image::Pixel(255, 101,  51), Image::Pixel(255, 153,  51), Image::Pixel(255, 203,  51), Image::Pixel(255, 255,  51) };
    const std::vector<Image::Pixel> col1 = { Image::Pixel(255, 101, 153), Image::Pixel(255, 153, 153), Image::Pixel(255, 204, 153), Image::Pixel(255, 255, 153) };
    const std::vector<Image::Pixel> col2 = { Image::Pixel(255, 101, 255), Image::Pixel(255, 153, 255), Image::Pixel(255, 205, 255), Image::Pixel(255, 255, 255) };

    const Image image({std::move(col0), std::move(col1), std::move(col2)});
    SeamCarver carver(std::move(image));

    std::vector<size_t> seam = carver.FindVerticalSeam();
    ASSERT_EQ(4, seam.size());
    EXPECT_EQ(0, seam.at(0));
    EXPECT_EQ(0, seam.at(1));
    EXPECT_EQ(0, seam.at(2));
    EXPECT_EQ(0, seam.at(3));

    carver.RemoveVerticalSeam(seam);
    ASSERT_EQ(2, carver.GetImageWidth());
    ASSERT_EQ(4, carver.GetImageHeight());
}