cmake_minimum_required(VERSION 3.23)
project(openglproject)

set(CMAKE_CXX_STANDARD 14)

include_directories(glm/glm)
include_directories(glm/glm/detail)
include_directories(glm/glm/gtc)
include_directories(glm/glm/gtx)
include_directories(glm/glm/simd)
include_directories(glm/test/external/gli)
include_directories(glm/test/external/gli/core)
include_directories(glm/test/external/gli/gtx)
include_directories(SOIL2TOOL/include)
include_directories(SOIL2TOOL/include/SOIL2)
include_directories(src)

add_executable(openglproject
        glm/glm/detail/_features.hpp
        glm/glm/detail/_fixes.hpp
        glm/glm/detail/_noise.hpp
        glm/glm/detail/_swizzle.hpp
        glm/glm/detail/_swizzle_func.hpp
        glm/glm/detail/_vectorize.hpp
        glm/glm/detail/dummy.cpp
        glm/glm/detail/func_common.hpp
        glm/glm/detail/func_common.inl
        glm/glm/detail/func_common_simd.inl
        glm/glm/detail/func_exponential.hpp
        glm/glm/detail/func_exponential.inl
        glm/glm/detail/func_exponential_simd.inl
        glm/glm/detail/func_geometric.hpp
        glm/glm/detail/func_geometric.inl
        glm/glm/detail/func_geometric_simd.inl
        glm/glm/detail/func_integer.hpp
        glm/glm/detail/func_integer.inl
        glm/glm/detail/func_integer_simd.inl
        glm/glm/detail/func_matrix.hpp
        glm/glm/detail/func_matrix.inl
        glm/glm/detail/func_matrix_simd.inl
        glm/glm/detail/func_packing.hpp
        glm/glm/detail/func_packing.inl
        glm/glm/detail/func_packing_simd.inl
        glm/glm/detail/func_trigonometric.hpp
        glm/glm/detail/func_trigonometric.inl
        glm/glm/detail/func_trigonometric_simd.inl
        glm/glm/detail/func_vector_relational.hpp
        glm/glm/detail/func_vector_relational.inl
        glm/glm/detail/func_vector_relational_simd.inl
        glm/glm/detail/glm.cpp
        glm/glm/detail/precision.hpp
        glm/glm/detail/setup.hpp
        glm/glm/detail/type_float.hpp
        glm/glm/detail/type_gentype.hpp
        glm/glm/detail/type_gentype.inl
        glm/glm/detail/type_half.hpp
        glm/glm/detail/type_half.inl
        glm/glm/detail/type_int.hpp
        glm/glm/detail/type_mat.hpp
        glm/glm/detail/type_mat.inl
        glm/glm/detail/type_mat2x2.hpp
        glm/glm/detail/type_mat2x2.inl
        glm/glm/detail/type_mat2x3.hpp
        glm/glm/detail/type_mat2x3.inl
        glm/glm/detail/type_mat2x4.hpp
        glm/glm/detail/type_mat2x4.inl
        glm/glm/detail/type_mat3x2.hpp
        glm/glm/detail/type_mat3x2.inl
        glm/glm/detail/type_mat3x3.hpp
        glm/glm/detail/type_mat3x3.inl
        glm/glm/detail/type_mat3x4.hpp
        glm/glm/detail/type_mat3x4.inl
        glm/glm/detail/type_mat4x2.hpp
        glm/glm/detail/type_mat4x2.inl
        glm/glm/detail/type_mat4x3.hpp
        glm/glm/detail/type_mat4x3.inl
        glm/glm/detail/type_mat4x4.hpp
        glm/glm/detail/type_mat4x4.inl
        glm/glm/detail/type_mat4x4_simd.inl
        glm/glm/detail/type_vec.hpp
        glm/glm/detail/type_vec.inl
        glm/glm/detail/type_vec1.hpp
        glm/glm/detail/type_vec1.inl
        glm/glm/detail/type_vec2.hpp
        glm/glm/detail/type_vec2.inl
        glm/glm/detail/type_vec3.hpp
        glm/glm/detail/type_vec3.inl
        glm/glm/detail/type_vec4.hpp
        glm/glm/detail/type_vec4.inl
        glm/glm/detail/type_vec4_simd.inl
        glm/glm/gtc/bitfield.hpp
        glm/glm/gtc/bitfield.inl
        glm/glm/gtc/color_encoding.inl
        glm/glm/gtc/color_space.hpp
        glm/glm/gtc/color_space.inl
        glm/glm/gtc/constants.hpp
        glm/glm/gtc/constants.inl
        glm/glm/gtc/epsilon.hpp
        glm/glm/gtc/epsilon.inl
        glm/glm/gtc/functions.hpp
        glm/glm/gtc/functions.inl
        glm/glm/gtc/integer.hpp
        glm/glm/gtc/integer.inl
        glm/glm/gtc/matrix_access.hpp
        glm/glm/gtc/matrix_access.inl
        glm/glm/gtc/matrix_integer.hpp
        glm/glm/gtc/matrix_inverse.hpp
        glm/glm/gtc/matrix_inverse.inl
        glm/glm/gtc/matrix_transform.hpp
        glm/glm/gtc/matrix_transform.inl
        glm/glm/gtc/noise.hpp
        glm/glm/gtc/noise.inl
        glm/glm/gtc/packing.hpp
        glm/glm/gtc/packing.inl
        glm/glm/gtc/quaternion.hpp
        glm/glm/gtc/quaternion.inl
        glm/glm/gtc/quaternion_simd.inl
        glm/glm/gtc/random.hpp
        glm/glm/gtc/random.inl
        glm/glm/gtc/reciprocal.hpp
        glm/glm/gtc/reciprocal.inl
        glm/glm/gtc/round.hpp
        glm/glm/gtc/round.inl
        glm/glm/gtc/type_aligned.hpp
        glm/glm/gtc/type_precision.hpp
        glm/glm/gtc/type_precision.inl
        glm/glm/gtc/type_ptr.hpp
        glm/glm/gtc/type_ptr.inl
        glm/glm/gtc/ulp.hpp
        glm/glm/gtc/ulp.inl
        glm/glm/gtc/vec1.hpp
        glm/glm/gtc/vec1.inl
        glm/glm/gtx/associated_min_max.hpp
        glm/glm/gtx/associated_min_max.inl
        glm/glm/gtx/bit.hpp
        glm/glm/gtx/bit.inl
        glm/glm/gtx/closest_point.hpp
        glm/glm/gtx/closest_point.inl
        glm/glm/gtx/color_space.hpp
        glm/glm/gtx/color_space.inl
        glm/glm/gtx/color_space_YCoCg.hpp
        glm/glm/gtx/color_space_YCoCg.inl
        glm/glm/gtx/common.hpp
        glm/glm/gtx/common.inl
        glm/glm/gtx/compatibility.hpp
        glm/glm/gtx/compatibility.inl
        glm/glm/gtx/component_wise.hpp
        glm/glm/gtx/component_wise.inl
        glm/glm/gtx/dual_quaternion.hpp
        glm/glm/gtx/dual_quaternion.inl
        glm/glm/gtx/euler_angles.hpp
        glm/glm/gtx/euler_angles.inl
        glm/glm/gtx/extend.hpp
        glm/glm/gtx/extend.inl
        glm/glm/gtx/extended_min_max.hpp
        glm/glm/gtx/extended_min_max.inl
        glm/glm/gtx/fast_exponential.hpp
        glm/glm/gtx/fast_exponential.inl
        glm/glm/gtx/fast_square_root.hpp
        glm/glm/gtx/fast_square_root.inl
        glm/glm/gtx/fast_trigonometry.hpp
        glm/glm/gtx/fast_trigonometry.inl
        glm/glm/gtx/float_notmalize.inl
        glm/glm/gtx/gradient_paint.hpp
        glm/glm/gtx/gradient_paint.inl
        glm/glm/gtx/handed_coordinate_space.hpp
        glm/glm/gtx/handed_coordinate_space.inl
        glm/glm/gtx/hash.hpp
        glm/glm/gtx/hash.inl
        glm/glm/gtx/integer.hpp
        glm/glm/gtx/integer.inl
        glm/glm/gtx/intersect.hpp
        glm/glm/gtx/intersect.inl
        glm/glm/gtx/io.hpp
        glm/glm/gtx/io.inl
        glm/glm/gtx/log_base.hpp
        glm/glm/gtx/log_base.inl
        glm/glm/gtx/matrix_cross_product.hpp
        glm/glm/gtx/matrix_cross_product.inl
        glm/glm/gtx/matrix_decompose.hpp
        glm/glm/gtx/matrix_decompose.inl
        glm/glm/gtx/matrix_interpolation.hpp
        glm/glm/gtx/matrix_interpolation.inl
        glm/glm/gtx/matrix_major_storage.hpp
        glm/glm/gtx/matrix_major_storage.inl
        glm/glm/gtx/matrix_operation.hpp
        glm/glm/gtx/matrix_operation.inl
        glm/glm/gtx/matrix_query.hpp
        glm/glm/gtx/matrix_query.inl
        glm/glm/gtx/matrix_transform_2d.hpp
        glm/glm/gtx/matrix_transform_2d.inl
        glm/glm/gtx/mixed_product.hpp
        glm/glm/gtx/mixed_product.inl
        glm/glm/gtx/norm.hpp
        glm/glm/gtx/norm.inl
        glm/glm/gtx/normal.hpp
        glm/glm/gtx/normal.inl
        glm/glm/gtx/normalize_dot.hpp
        glm/glm/gtx/normalize_dot.inl
        glm/glm/gtx/number_precision.hpp
        glm/glm/gtx/number_precision.inl
        glm/glm/gtx/optimum_pow.hpp
        glm/glm/gtx/optimum_pow.inl
        glm/glm/gtx/orthonormalize.hpp
        glm/glm/gtx/orthonormalize.inl
        glm/glm/gtx/perpendicular.hpp
        glm/glm/gtx/perpendicular.inl
        glm/glm/gtx/polar_coordinates.hpp
        glm/glm/gtx/polar_coordinates.inl
        glm/glm/gtx/projection.hpp
        glm/glm/gtx/projection.inl
        glm/glm/gtx/quaternion.hpp
        glm/glm/gtx/quaternion.inl
        glm/glm/gtx/range.hpp
        glm/glm/gtx/raw_data.hpp
        glm/glm/gtx/raw_data.inl
        glm/glm/gtx/rotate_normalized_axis.hpp
        glm/glm/gtx/rotate_normalized_axis.inl
        glm/glm/gtx/rotate_vector.hpp
        glm/glm/gtx/rotate_vector.inl
        glm/glm/gtx/scalar_multiplication.hpp
        glm/glm/gtx/scalar_relational.hpp
        glm/glm/gtx/scalar_relational.inl
        glm/glm/gtx/simd_mat4.hpp
        glm/glm/gtx/simd_mat4.inl
        glm/glm/gtx/simd_quat.hpp
        glm/glm/gtx/simd_quat.inl
        glm/glm/gtx/simd_vec4.hpp
        glm/glm/gtx/simd_vec4.inl
        glm/glm/gtx/spline.hpp
        glm/glm/gtx/spline.inl
        glm/glm/gtx/std_based_type.hpp
        glm/glm/gtx/std_based_type.inl
        glm/glm/gtx/string_cast.hpp
        glm/glm/gtx/string_cast.inl
        glm/glm/gtx/transform.hpp
        glm/glm/gtx/transform.inl
        glm/glm/gtx/transform2.hpp
        glm/glm/gtx/transform2.inl
        glm/glm/gtx/type_aligned.hpp
        glm/glm/gtx/type_aligned.inl
        glm/glm/gtx/type_trait.hpp
        glm/glm/gtx/type_trait.inl
        glm/glm/gtx/vector_angle.hpp
        glm/glm/gtx/vector_angle.inl
        glm/glm/gtx/vector_query.hpp
        glm/glm/gtx/vector_query.inl
        glm/glm/gtx/wrap.hpp
        glm/glm/gtx/wrap.inl
        glm/glm/simd/common.h
        glm/glm/simd/exponential.h
        glm/glm/simd/geometric.h
        glm/glm/simd/integer.h
        glm/glm/simd/matrix.h
        glm/glm/simd/packing.h
        glm/glm/simd/platform.h
        glm/glm/simd/trigonometric.h
        glm/glm/simd/vector_relational.h
        glm/glm/common.hpp
        glm/glm/exponential.hpp
        glm/glm/ext.hpp
        glm/glm/fwd.hpp
        glm/glm/geometric.hpp
        glm/glm/glm.hpp
        glm/glm/integer.hpp
        glm/glm/mat2x2.hpp
        glm/glm/mat2x3.hpp
        glm/glm/mat2x4.hpp
        glm/glm/mat3x2.hpp
        glm/glm/mat3x3.hpp
        glm/glm/mat3x4.hpp
        glm/glm/mat4x2.hpp
        glm/glm/mat4x3.hpp
        glm/glm/mat4x4.hpp
        glm/glm/matrix.hpp
        glm/glm/packing.hpp
        glm/glm/trigonometric.hpp
        glm/glm/vec2.hpp
        glm/glm/vec3.hpp
        glm/glm/vec4.hpp
        glm/glm/vector_relational.hpp
        glm/test/core/core_func_common.cpp
        glm/test/core/core_func_exponential.cpp
        glm/test/core/core_func_geometric.cpp
        glm/test/core/core_func_integer.cpp
        glm/test/core/core_func_integer_bit_count.cpp
        glm/test/core/core_func_integer_find_lsb.cpp
        glm/test/core/core_func_integer_find_msb.cpp
        glm/test/core/core_func_matrix.cpp
        glm/test/core/core_func_noise.cpp
        glm/test/core/core_func_packing.cpp
        glm/test/core/core_func_swizzle.cpp
        glm/test/core/core_func_trigonometric.cpp
        glm/test/core/core_func_vector_relational.cpp
        glm/test/core/core_setup_force_cxx98.cpp
        glm/test/core/core_setup_message.cpp
        glm/test/core/core_setup_precision.cpp
        glm/test/core/core_type_cast.cpp
        glm/test/core/core_type_ctor.cpp
        glm/test/core/core_type_float.cpp
        glm/test/core/core_type_int.cpp
        glm/test/core/core_type_length.cpp
        glm/test/core/core_type_mat2x2.cpp
        glm/test/core/core_type_mat2x3.cpp
        glm/test/core/core_type_mat2x4.cpp
        glm/test/core/core_type_mat3x2.cpp
        glm/test/core/core_type_mat3x3.cpp
        glm/test/core/core_type_mat3x4.cpp
        glm/test/core/core_type_mat4x2.cpp
        glm/test/core/core_type_mat4x3.cpp
        glm/test/core/core_type_mat4x4.cpp
        glm/test/core/core_type_vec1.cpp
        glm/test/core/core_type_vec2.cpp
        glm/test/core/core_type_vec3.cpp
        glm/test/core/core_type_vec4.cpp
        glm/test/external/gli/core/dummy.cpp
        glm/test/external/gli/core/generate_mipmaps.hpp
        glm/test/external/gli/core/generate_mipmaps.inl
        glm/test/external/gli/core/image2d.hpp
        glm/test/external/gli/core/image2d.inl
        glm/test/external/gli/core/operation.hpp
        glm/test/external/gli/core/operation.inl
        glm/test/external/gli/core/operator.hpp
        glm/test/external/gli/core/operator.inl
        glm/test/external/gli/core/shared_array.hpp
        glm/test/external/gli/core/shared_array.inl
        glm/test/external/gli/core/shared_ptr.hpp
        glm/test/external/gli/core/shared_ptr.inl
        glm/test/external/gli/core/size.hpp
        glm/test/external/gli/core/size.inl
        glm/test/external/gli/core/texture2d.hpp
        glm/test/external/gli/core/texture2d.inl
        glm/test/external/gli/core/texture2d_array.hpp
        glm/test/external/gli/core/texture2d_array.inl
        glm/test/external/gli/core/texture_cube.hpp
        glm/test/external/gli/core/texture_cube.inl
        glm/test/external/gli/core/texture_cube_array.hpp
        glm/test/external/gli/core/texture_cube_array.inl
        glm/test/external/gli/gtx/compression.hpp
        glm/test/external/gli/gtx/compression.inl
        glm/test/external/gli/gtx/fetch.hpp
        glm/test/external/gli/gtx/fetch.inl
        glm/test/external/gli/gtx/gl_texture2d.hpp
        glm/test/external/gli/gtx/gl_texture2d.inl
        glm/test/external/gli/gtx/gradient.hpp
        glm/test/external/gli/gtx/gradient.inl
        glm/test/external/gli/gtx/loader.hpp
        glm/test/external/gli/gtx/loader.inl
        glm/test/external/gli/gtx/loader_dds10.hpp
        glm/test/external/gli/gtx/loader_dds10.inl
        glm/test/external/gli/gtx/loader_dds9.hpp
        glm/test/external/gli/gtx/loader_dds9.inl
        glm/test/external/gli/gtx/loader_tga.hpp
        glm/test/external/gli/gtx/loader_tga.inl
        glm/test/external/gli/gtx/wavelet.hpp
        glm/test/external/gli/gtx/wavelet.inl
        glm/test/external/gli/gli.hpp
        glm/test/gtc/gtc_bitfield.cpp
        glm/test/gtc/gtc_color_space.cpp
        glm/test/gtc/gtc_constants.cpp
        glm/test/gtc/gtc_epsilon.cpp
        glm/test/gtc/gtc_functions.cpp
        glm/test/gtc/gtc_integer.cpp
        glm/test/gtc/gtc_matrix_access.cpp
        glm/test/gtc/gtc_matrix_integer.cpp
        glm/test/gtc/gtc_matrix_inverse.cpp
        glm/test/gtc/gtc_matrix_transform.cpp
        glm/test/gtc/gtc_noise.cpp
        glm/test/gtc/gtc_packing.cpp
        glm/test/gtc/gtc_quaternion.cpp
        glm/test/gtc/gtc_random.cpp
        glm/test/gtc/gtc_reciprocal.cpp
        glm/test/gtc/gtc_round.cpp
        glm/test/gtc/gtc_type_aligned.cpp
        glm/test/gtc/gtc_type_precision.cpp
        glm/test/gtc/gtc_type_ptr.cpp
        glm/test/gtc/gtc_ulp.cpp
        glm/test/gtc/gtc_user_defined_types.cpp
        glm/test/gtc/gtc_vec1.cpp
        glm/test/gtx/gtx_associated_min_max.cpp
        glm/test/gtx/gtx_closest_point.cpp
        glm/test/gtx/gtx_color_space.cpp
        glm/test/gtx/gtx_color_space_YCoCg.cpp
        glm/test/gtx/gtx_common.cpp
        glm/test/gtx/gtx_compatibility.cpp
        glm/test/gtx/gtx_component_wise.cpp
        glm/test/gtx/gtx_dual_quaternion.cpp
        glm/test/gtx/gtx_euler_angle.cpp
        glm/test/gtx/gtx_extend.cpp
        glm/test/gtx/gtx_extended_min_max.cpp
        glm/test/gtx/gtx_extented_min_max.cpp
        glm/test/gtx/gtx_fast_exponential.cpp
        glm/test/gtx/gtx_fast_square_root.cpp
        glm/test/gtx/gtx_fast_trigonometry.cpp
        glm/test/gtx/gtx_gradient_paint.cpp
        glm/test/gtx/gtx_handed_coordinate_space.cpp
        glm/test/gtx/gtx_int_10_10_10_2.cpp
        glm/test/gtx/gtx_integer.cpp
        glm/test/gtx/gtx_intersect.cpp
        glm/test/gtx/gtx_io.cpp
        glm/test/gtx/gtx_log_base.cpp
        glm/test/gtx/gtx_matrix_cross_product.cpp
        glm/test/gtx/gtx_matrix_decompose.cpp
        glm/test/gtx/gtx_matrix_interpolation.cpp
        glm/test/gtx/gtx_matrix_major_storage.cpp
        glm/test/gtx/gtx_matrix_operation.cpp
        glm/test/gtx/gtx_matrix_query.cpp
        glm/test/gtx/gtx_matrix_transform_2d.cpp
        glm/test/gtx/gtx_mixed_product.cpp
        glm/test/gtx/gtx_norm.cpp
        glm/test/gtx/gtx_normal.cpp
        glm/test/gtx/gtx_normalize_dot.cpp
        glm/test/gtx/gtx_number_precision.cpp
        glm/test/gtx/gtx_optimum_pow.cpp
        glm/test/gtx/gtx_orthonormalize.cpp
        glm/test/gtx/gtx_perpendicular.cpp
        glm/test/gtx/gtx_polar_coordinates.cpp
        glm/test/gtx/gtx_projection.cpp
        glm/test/gtx/gtx_quaternion.cpp
        glm/test/gtx/gtx_random.cpp
        glm/test/gtx/gtx_range.cpp
        glm/test/gtx/gtx_rotate_normalized_axis.cpp
        glm/test/gtx/gtx_rotate_vector.cpp
        glm/test/gtx/gtx_scalar_multiplication.cpp
        glm/test/gtx/gtx_scalar_relational.cpp
        glm/test/gtx/gtx_simd_mat4.cpp
        glm/test/gtx/gtx_simd_vec4.cpp
        glm/test/gtx/gtx_spline.cpp
        glm/test/gtx/gtx_string_cast.cpp
        glm/test/gtx/gtx_type_aligned.cpp
        glm/test/gtx/gtx_type_trait.cpp
        glm/test/gtx/gtx_vector_angle.cpp
        glm/test/gtx/gtx_vector_query.cpp
        glm/test/gtx/gtx_wrap.cpp
        SOIL2TOOL/include/SOIL2/image_DXT.c
        SOIL2TOOL/include/SOIL2/image_DXT.h
        SOIL2TOOL/include/SOIL2/image_helper.c
        SOIL2TOOL/include/SOIL2/image_helper.h
        SOIL2TOOL/include/SOIL2/jo_jpeg.h
        SOIL2TOOL/include/SOIL2/pkm_helper.h
        SOIL2TOOL/include/SOIL2/pvr_helper.h
        SOIL2TOOL/include/SOIL2/SOIL2.c
        SOIL2TOOL/include/SOIL2/SOIL2.h
        SOIL2TOOL/include/SOIL2/stb_image.h
        SOIL2TOOL/include/SOIL2/stb_image_write.h
        SOIL2TOOL/include/SOIL2/stbi_DDS.h
        SOIL2TOOL/include/SOIL2/stbi_DDS_c.h
        SOIL2TOOL/include/SOIL2/stbi_ext.h
        SOIL2TOOL/include/SOIL2/stbi_ext_c.h
        SOIL2TOOL/include/SOIL2/stbi_pkm.h
        SOIL2TOOL/include/SOIL2/stbi_pkm_c.h
        SOIL2TOOL/include/SOIL2/stbi_pvr.h
        SOIL2TOOL/include/SOIL2/stbi_pvr_c.h
        SOIL2TOOL/include/SOIL2/wfETC.c
        SOIL2TOOL/include/SOIL2/wfETC.h
        src/helloworld.cpp
        src/openglproject.cpp
        src/pipeline_test.cpp
        src/Shader.h
        src/soil_test.cpp
        src/soil_test_2.cpp
        src/transform_3D.cpp
        src/Uniform_test.cpp)
