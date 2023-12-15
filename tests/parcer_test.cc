#include "../model/model.h"
#include <gtest/gtest.h>

#include "../viewer_data.h"
#include <cmath>

static constexpr float kEps = 1E-6;

TEST(Datsun, TestOne) {
    s21::Model obj;
    obj = "object_files/Datsun_280Z.obj";
    std::vector<float> v = obj.get_vertexes();
    EXPECT_NEAR(v[0], 0.700740, kEps);
    EXPECT_NEAR(v[1], 0.136954, kEps);
    EXPECT_NEAR(v[2], 0.669096, kEps);
    std::vector<unsigned int> f = obj.get_polygons();
    EXPECT_EQ(f[f.size() - 6], 59060);
    EXPECT_EQ(f[f.size() - 5], 59059);
    EXPECT_EQ(f[f.size() - 4], 59059);
    EXPECT_EQ(f[f.size() - 3], 59043);
    EXPECT_EQ(f[f.size() - 2], 59043);
    EXPECT_EQ(f[f.size() - 1], 59060);
}

TEST(Cube, TestOne) {
    s21::Model  obj;
    obj = "object_files/cube.obj";
    std::vector<float> v = obj.get_vertexes();
    size_t last_v = v.size() - 1;
    EXPECT_NEAR(v[0], 1.0, kEps);
    EXPECT_NEAR(v[1], -1.0, kEps);
    EXPECT_NEAR(v[2], -1.0, kEps);
    EXPECT_NEAR(v[last_v -2], -1.0, kEps);
    EXPECT_NEAR(v[last_v -1], 1.0, kEps);
    EXPECT_NEAR(v[last_v], -1.0, kEps);
    std::vector<unsigned int> f = obj.get_polygons();
    EXPECT_EQ(f[0], 1);
    EXPECT_EQ(f[1], 2);
    EXPECT_EQ(f[2], 2);
    EXPECT_EQ(f[3], 3);
    EXPECT_EQ(f[4], 3);
    EXPECT_EQ(f[5], 1);
    size_t position = f.size() - 1;
    EXPECT_EQ(f[position - 5], 4);
    EXPECT_EQ(f[position - 4], 0);
    EXPECT_EQ(f[position - 3], 0);
    EXPECT_EQ(f[position - 2], 7);
    EXPECT_EQ(f[position - 1], 7);
    EXPECT_EQ(f[position], 4);
}

TEST(Cube, TestTwo) {
    s21::Model  obj;
    obj = "object_files/cube.obj";
    std::vector<float> v = obj.get_vertexes();
    EXPECT_EQ(v.size()/3, 8);
    EXPECT_EQ(v.size()/3, obj.GetQuantityVertexes());
    std::vector<unsigned int> f = obj.get_polygons();
    EXPECT_EQ(f.size(), 72);
    EXPECT_EQ(f.size()/2, obj.GetQuantityFaces());
    EXPECT_EQ(12 * 3, obj.GetQuantityFaces());
}

TEST(Cube, TestRotateX) {
    s21::Model  obj;
    s21::Coordinates data;
    data.state = s21::Affine::kRotateX;
    data.rotate_value_x = 1;
    obj = "object_files/cube.obj";
    obj.AffineRotate(data);
    std::vector<float> v = obj.get_vertexes();
    float x = 1.0;
    float y = -1.0;
    float z = -1.0;
    float matrix[] {
        1,           0,            0,
        0, std::cos(1), -std::sin(1),
        0, std::sin(1),  std::cos(1)};
    float res_x = matrix[0] * x + matrix[1] * y + matrix[2] * z;
    float res_y = matrix[3] * x + matrix[4] * y + matrix[5] * z;
    float res_z = matrix[6] * x + matrix[7] * y + matrix[8] * z;

    EXPECT_NEAR(v[0], res_x, kEps);
    EXPECT_NEAR(v[1], res_y, kEps);
    EXPECT_NEAR(v[2], res_z, kEps);
}

TEST(Cube, TestRotateY) {
    s21::Model  obj;
    s21::Coordinates data;
    data.state = s21::Affine::kRotateY;
    data.rotate_value_y = -1;
    obj = "object_files/cube.obj";
    obj.AffineRotate(data);
    std::vector<float> v = obj.get_vertexes();
    float x = 1.0;
    float y = -1.0;
    float z = -1.0;
    float matrix[] {
         std::cos(-1), 0, std::sin(-1),
                    0, 1,            0,
        -std::sin(-1), 0, std::cos(-1)};
    float res_x = matrix[0] * x + matrix[1] * y + matrix[2] * z;
    float res_y = matrix[3] * x + matrix[4] * y + matrix[5] * z;
    float res_z = matrix[6] * x + matrix[7] * y + matrix[8] * z;

    EXPECT_NEAR(v[0], res_x, kEps);
    EXPECT_NEAR(v[1], res_y, kEps);
    EXPECT_NEAR(v[2], res_z, kEps);
}

TEST(Cube, TestRotateZ) {
    s21::Model  obj;
    s21::Coordinates data;
    data.state = s21::Affine::kRotateZ;
    data.rotate_value_z = 5;
    obj = "object_files/cube.obj";
    obj.AffineRotate(data);
    std::vector<float> v = obj.get_vertexes();
    float x = 1.0;
    float y = -1.0;
    float z = -1.0;
    float matrix[] {
        std::cos(5), -std::sin(5), 0,
        std::sin(5),  std::cos(5), 0,
                  0,            0, 1};
    float res_x = matrix[0] * x + matrix[1] * y + matrix[2] * z;
    float res_y = matrix[3] * x + matrix[4] * y + matrix[5] * z;
    float res_z = matrix[6] * x + matrix[7] * y + matrix[8] * z;

    EXPECT_NEAR(v[0], res_x, kEps);
    EXPECT_NEAR(v[1], res_y, kEps);
    EXPECT_NEAR(v[2], res_z, kEps);
}

TEST(Cube, TestScale) {
    s21::Model  obj;
    s21::Coordinates data;
    data.state = s21::Affine::kScale;
    data.scale_value = 1.88;
    obj = "object_files/cube.obj";
    obj.OtherMethods(data);
    std::vector<float> v = obj.get_vertexes();
    size_t last_v = v.size() - 1;

    EXPECT_NEAR(v[0],  1.0 * (data.scale_value + 1.0), kEps);
    EXPECT_NEAR(v[1], -1.0 * (data.scale_value + 1.0), kEps);
    EXPECT_NEAR(v[2], -1.0 * (data.scale_value + 1.0), kEps);
    EXPECT_NEAR(v[last_v -2], -1.0 * (data.scale_value + 1.0), kEps);
    EXPECT_NEAR(v[last_v -1],  1.0 * (data.scale_value + 1.0), kEps);
    EXPECT_NEAR(v[last_v], -1.0 * (data.scale_value + 1.0), kEps);
}

TEST(Ball, TestOne) {
    s21::Model  obj;
    obj = "object_files/Ball_OBJ.obj";
    std::vector<float> v = obj.get_vertexes();
    EXPECT_NEAR(v[0], -1.30948, kEps);
    EXPECT_NEAR(v[1], -1.05114, kEps);
    EXPECT_NEAR(v[2], -0.209404, kEps);
    std::vector<unsigned int> f = obj.get_polygons();
    size_t position = f.size() - 1;
    EXPECT_EQ(f[position - 5], 11356);
    EXPECT_EQ(f[position - 4], 11282);
    EXPECT_EQ(f[position - 3], 11282);
    EXPECT_EQ(f[position - 2], 11284);
    EXPECT_EQ(f[position - 1], 11284);
    EXPECT_EQ(f[position], 11356);
}

TEST(Skull, TestOne) {
    s21::Model  obj;
    obj = "object_files/skull.obj";
    std::vector<float> v = obj.get_vertexes();
    EXPECT_NEAR(v[0], -2.40469, kEps);
    EXPECT_NEAR(v[1], 2.71917, kEps);
    EXPECT_NEAR(v[2], -2.89007, kEps);
    std::vector<unsigned int> f = obj.get_polygons();
    size_t position = f.size() - 1;
    EXPECT_EQ(f[position - 5], 5783);
    EXPECT_EQ(f[position - 4], 5755);
    EXPECT_EQ(f[position - 3], 5755);
    EXPECT_EQ(f[position - 2], 5735);
    EXPECT_EQ(f[position - 1], 5735);
    EXPECT_EQ(f[position], 5783);
}


TEST(Empty, TestOne) {
    s21::Model  obj;
    obj = "object_files/empty.obj";
    std::vector<float> v = obj.get_vertexes();
    EXPECT_EQ(v.size(), 0);

    std::vector<unsigned int> f = obj.get_polygons();
    EXPECT_EQ(f.size(), 0);
    EXPECT_EQ(obj.GetQuantityVertexes(), 0);
    EXPECT_EQ(obj.GetQuantityFaces(), 0);
}

TEST(NoCorrectName, TestOne) {
    s21::Model  obj;
    EXPECT_THROW(obj = "object_files/sadfrasdf.obj", std::ios_base::failure);
}
