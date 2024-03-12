# Copyright 2023 The gRPC Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
This file is generated by generate_dockerimage_current_versions_bzl.sh
It makes the info from testing docker image *.current_version files
accessible to bazel builds.
"""

DOCKERIMAGE_CURRENT_VERSIONS = {
    "third_party/rake-compiler-dock/rake_aarch64-linux.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_aarch64-linux@sha256:2ab21c63fc49cd56e2d083d5219dc67134de0e1465edddb3f87e9efdc538910b",
    "third_party/rake-compiler-dock/rake_arm64-darwin.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_arm64-darwin@sha256:16bb1a0746215557f5577e4cd289e10cec593d74b5a3033c9bb2ab4bc3c6662f",
    "third_party/rake-compiler-dock/rake_x64-mingw-ucrt.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x64-mingw-ucrt@sha256:8392ae8ca347a6ce4a140ada7c24135de8744523282ad94eef389eafc9f4397e",
    "third_party/rake-compiler-dock/rake_x64-mingw32.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x64-mingw32@sha256:b97c530e1f2b1bd793c743fc961d21b8a52b2dbb8c4d06b3dcf3fce5d8b99500",
    "third_party/rake-compiler-dock/rake_x86-linux.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86-linux@sha256:facd2d03737e64f615335156c726b1284f44fff1ae83b1c06fa0c39c176df04a",
    "third_party/rake-compiler-dock/rake_x86-mingw32.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86-mingw32@sha256:41f92a60b2b8bec72f3772cb0644860d00c0475b6acdc7062abdd01e6667e3e6",
    "third_party/rake-compiler-dock/rake_x86_64-darwin.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86_64-darwin@sha256:ba8e38140f69ae8febe01f8b168782ec1f15cd2e59dd61719fd1176404138062",
    "third_party/rake-compiler-dock/rake_x86_64-linux.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86_64-linux@sha256:149b949cfe4968963d86dca7e4bc425201efb6be912a996aff952b0003f25ad0",
    "tools/dockerfile/distribtest/cpp_debian10_aarch64_cross_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cpp_debian10_aarch64_cross_x64@sha256:15eeafcd816cb32a0d44da22f654749352a92fec9626dc028b39948897d5bea3",
    "tools/dockerfile/distribtest/cpp_debian10_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cpp_debian10_x64@sha256:904e3db8521697768f94aa08230063b474246184e126f74a41b98a6f4aaf6a49",
    "tools/dockerfile/distribtest/csharp_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_alpine_x64@sha256:915880cb29ea83cc3aabb3bc0f2025cc36b0a09894552bff041e3b2426e08c48",
    "tools/dockerfile/distribtest/csharp_centos7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_centos7_x64@sha256:ec715dd5fbd621789e7598c8d4ac346a7b4037b0cc83fbb29990dc8e4c1f1a13",
    "tools/dockerfile/distribtest/csharp_debian10_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_debian10_x64@sha256:98cf90c3039940e2f220d1c63688428aa14bb35e89e37894e999b3490001197b",
    "tools/dockerfile/distribtest/csharp_dotnet31_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_dotnet31_x64@sha256:aeea1911ea20606bb409e9b8ac68c7b4127fee2be7dcbf9382f2a26b9c865ed0",
    "tools/dockerfile/distribtest/csharp_dotnet5_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_dotnet5_x64@sha256:2cf597a37f77da51f606b603ee2923c5fac604ab355d316c31059e1c4daef24f",
    "tools/dockerfile/distribtest/csharp_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_ubuntu2204_x64@sha256:4d17c8394af37687e588a732947c82ca7efca1f58397047569614bffc902bf02",
    "tools/dockerfile/distribtest/php7_debian10_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php7_debian10_x64@sha256:e760a60f2dce2dada571d9b07447a9f99ffeeb366a309dbbb5dc0a43991c22dc",
    "tools/dockerfile/distribtest/python_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_alpine_x64@sha256:699ac7b86199406fa27e88f30a1c623ef34ac33f6d9330fd13a6f6457ee4e19f",
    "tools/dockerfile/distribtest/python_arch_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_arch_x64@sha256:2c1adadeb010e107132cf5137f32a2d18727796631245b110cc74f69c07502e1",
    "tools/dockerfile/distribtest/python_buster_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_buster_x64@sha256:e501dc8e2f4ab9cd4382974759a879a27c065c8fed5327f538764298fc5c4972",
    "tools/dockerfile/distribtest/python_buster_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_buster_x86@sha256:185fbb174525d67b6146f4d233c804c589b0b57d783bb1bf95bc47cfe792754e",
    "tools/dockerfile/distribtest/python_centos7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_centos7_x64@sha256:39afaa687cb8516eef1621ed789326fdde2014fd3c81d11a1ded72f2d5285fe1",
    "tools/dockerfile/distribtest/python_dev_alpine3.7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_alpine3.7_x64@sha256:7c08f67211a49eb72ad08c29de5c64a914c066d9c1670b712e717571b8d5c7e2",
    "tools/dockerfile/distribtest/python_dev_arch_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_arch_x64@sha256:29f179ef2083ee6addd57e90f58781fdc1cb5dc3dd3e228da1af38785b921f35",
    "tools/dockerfile/distribtest/python_dev_buster_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_buster_x64@sha256:e30d6efdeac24e5136cc169d503a239df22147bfb121d27feb1f87d58a8fe64e",
    "tools/dockerfile/distribtest/python_dev_buster_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_buster_x86@sha256:179146fd5d5cc15846c6bf0284c2e261f383caf944559d2d9f7a5af0e0f7152d",
    "tools/dockerfile/distribtest/python_dev_centos7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_centos7_x64@sha256:e6e9a1b23a0a543050db91e17d621aa899bad04308adaf961c11fa88ba941a95",
    "tools/dockerfile/distribtest/python_dev_fedora36_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_fedora36_x64@sha256:d10ea0c54ecaa861b67942b4adc69178585cd071c9d0c8997fa274a362beea55",
    "tools/dockerfile/distribtest/python_dev_ubuntu2004_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_ubuntu2004_x64@sha256:91f0d88c43ec52ecd63f99acb424c88ff9a67fa046fae207a75e99bee37eef11",
    "tools/dockerfile/distribtest/python_dev_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_ubuntu2204_x64@sha256:9e6c9ddc738afcd73fcf2de27b22fdc22a74f1e90e214345838373d9c65ea215",
    "tools/dockerfile/distribtest/python_fedora36_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_fedora36_x64@sha256:85b2d2fbbcfc1b995ce3916dcf8240c29dbc72f91bd47f04187c2db008570ba4",
    "tools/dockerfile/distribtest/python_opensuse_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_opensuse_x64@sha256:da52566b078d10e537aa219e59641731a57e5dc7d17d6737f5e5a7d447acf5cc",
    "tools/dockerfile/distribtest/python_python38_buster_aarch64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_python38_buster_aarch64@sha256:487b9af2ad1459ee2630694e61074d4ac525d4f90b2bdb026dbf6f77fb3e9878",
    "tools/dockerfile/distribtest/python_ubuntu2004_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_ubuntu2004_x64@sha256:342e9dc23b674ad256b220745745be818708a1baa25a2690f0d4f777e28a22a3",
    "tools/dockerfile/distribtest/python_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_ubuntu2204_x64@sha256:b6ca497348741615406d1d571cf5042008da934c4f708877aa06a66b5dc3036c",
    "tools/dockerfile/distribtest/ruby_centos7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_centos7_x64@sha256:4d529b984b78ca179086f7f9b416605e2d9a96ca0a28a71f4421bb5ffdc18f96",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_0.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_0@sha256:ed855e283001ea9f526aea3830e93c2138194e1740cf6aa5e11a19f6d81e0e22",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_1.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_1@sha256:17e3f48a1e1ec2caade5ce4db73f92d6f1f27b34d7cba61968d8b3e3d15f9ca3",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_2.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_2@sha256:aa5bf946f601a3ee557be63816428e6a4c997f33194c1a58499d0ca17e7bf562",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_3.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_3@sha256:7643e5e91e9f24dc403ad967372c6a6b9a92ccb98fddaa5c29087e5e4ddb1f11",
    "tools/dockerfile/distribtest/ruby_ubuntu2004_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_ubuntu2004_x64@sha256:426cbf625df0c0e7451b9716041996dc6a35a3788c1a24d68891256f84733d8e",
    "tools/dockerfile/distribtest/ruby_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_ubuntu2204_x64@sha256:1c74c312f8a4ab37e629732a35daa3056e12136b90f37540cdf9fa11303c7eb8",
    "tools/dockerfile/grpc_artifact_centos6_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_centos6_x64@sha256:3285047265ea2b7c5d4df4c769b2d05f56288d947c75e16d27ae2dee693f791b",
    "tools/dockerfile/grpc_artifact_centos6_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_centos6_x86@sha256:19783239da92208f0f39cf563529cd02e889920497ef81c60d20391fa998af62",
    "tools/dockerfile/grpc_artifact_protoc_aarch64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_protoc_aarch64@sha256:1a3957f32e81259e6f3c602bd67feb132ebc5a5f23e9cb0bf63ba34b91185982",
    "tools/dockerfile/grpc_artifact_python_linux_armv7.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_linux_armv7@sha256:f109d6c22cadb053f6843a66ee827d74f34d6cbf75a32f455a9da099ed1bdc9c",
    "tools/dockerfile/grpc_artifact_python_manylinux2014_aarch64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_manylinux2014_aarch64@sha256:ef3ae7991763a499b7a0317fd628d1c9d1eef7931fb160361d230f2009febdc3",
    "tools/dockerfile/grpc_artifact_python_manylinux2014_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_manylinux2014_x64@sha256:0725226dfb1f707ed3cb2d7cafb2376c33fa89d58577bf80e1d76a0c3bc92c64",
    "tools/dockerfile/grpc_artifact_python_manylinux2014_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_manylinux2014_x86@sha256:8d00dc61594f4fa05ada5c38d55627f139a73cd3a6e4fbc0907a866f2a5f5b17",
    "tools/dockerfile/grpc_artifact_python_musllinux_1_1_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_musllinux_1_1_x64@sha256:a53a196823862af50ec05d0c5092f765438b488772d1bf53f431cbc98233403d",
    "tools/dockerfile/grpc_artifact_python_musllinux_1_1_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_musllinux_1_1_x86@sha256:3b0892b4d7c751781fe7947d785837cb5a9c9768519066a4e755838acdfd3ad6",
    "tools/dockerfile/interoptest/grpc_interop_aspnetcore.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_aspnetcore@sha256:8e2e732e78724a8382c340dca72e7653c5f82c251a3110fa2874cc00ba538878",
    "tools/dockerfile/interoptest/grpc_interop_cxx.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_cxx@sha256:5a0b1690e6eb63d0904786da9daf6e9a66c901dc7b73d97b4652c05473401790",
    "tools/dockerfile/interoptest/grpc_interop_dart.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_dart@sha256:5e335005b27709f0882c5723affafa55094bd27a0cda7ce91c718deed157f2bb",
    "tools/dockerfile/interoptest/grpc_interop_go.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go@sha256:889e7ff34399a5e16af87940d1eaa239e56da307f7faca3f8f1d28379c2e3df3",
    "tools/dockerfile/interoptest/grpc_interop_go1.11.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.11@sha256:29cde59287843a3208c0cabeaf430cf813846a738c8a1b9692e68b54bbbdcc2d",
    "tools/dockerfile/interoptest/grpc_interop_go1.16.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.16@sha256:d5b2b0c02e7a8196fea704196a8221994983c22eece2ac2324e095e8972a957f",
    "tools/dockerfile/interoptest/grpc_interop_go1.19.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.19@sha256:889e7ff34399a5e16af87940d1eaa239e56da307f7faca3f8f1d28379c2e3df3",
    "tools/dockerfile/interoptest/grpc_interop_go1.8.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.8@sha256:7830a301b37539252c592b9cd7fa30a6142d0afc717a05fc8d2b82c74fb45efe",
    "tools/dockerfile/interoptest/grpc_interop_http2.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_http2@sha256:e3f247d8038374848fadf7215b841e3575c0b2a4217feb503a79b8004b164c5a",
    "tools/dockerfile/interoptest/grpc_interop_java.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_java@sha256:d9210764071662ba2f377dafcaff4b743f41e4dff1876dd47df7b1c6950f88af",
    "tools/dockerfile/interoptest/grpc_interop_node.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_node@sha256:92f946fc9ff71d79bf1f1a0dff2b2eb38b51d5ff27a77a92fe317a776d64a3ef",
    "tools/dockerfile/interoptest/grpc_interop_nodepurejs.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_nodepurejs@sha256:76925722a5cce232e2e0fa459a5119e47606318af6c77a4a973ca4e7da2e1a9d",
    "tools/dockerfile/interoptest/grpc_interop_php7.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_php7@sha256:9342ff81689c37d9e79fd6abcc08bf310eb48174e83bd3bfce39d225c02f0d4e",
    "tools/dockerfile/interoptest/grpc_interop_python.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_python@sha256:1f55faacfb4be587e6d26b05561e79bf3e17fe81c69a990e8aeca4257081c9ac",
    "tools/dockerfile/interoptest/grpc_interop_pythonasyncio.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_pythonasyncio@sha256:47127a7863097b436613885a8866a2ef055470452838ceebb31f692ac88ac1d1",
    "tools/dockerfile/interoptest/grpc_interop_ruby.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_ruby@sha256:efd7f41a736dd4b8f73b32f5215b86f6bfe9013c422dfcd77978de0253aaee45",
    "tools/dockerfile/interoptest/lb_interop_fake_servers.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/lb_interop_fake_servers@sha256:b89a51dd9147e1293f50ee64dd719fce5929ca7894d3770a3d80dbdecb99fd52",
    "tools/dockerfile/test/android_ndk.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/android_ndk@sha256:ab154ecb062af2111d2d3550c4d3da3384201d9893bbd37d49e8160fc34bc137",
    "tools/dockerfile/test/bazel.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/bazel@sha256:13ac6e425df68bcbee5898bb349171781597416bb93a84c4b923390e078602be",
    "tools/dockerfile/test/bazel_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/bazel_arm64@sha256:112e4f5085b43df2c02852f23c665aa5310e5a44ea3f4ae553a21b882a9b56aa",
    "tools/dockerfile/test/binder_transport_apk.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/binder_transport_apk@sha256:498798c02e414c19c85781c245ca641f94f1494a47edec7861316d91b2d635e5",
    "tools/dockerfile/test/csharp_debian11_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_debian11_arm64@sha256:4d4bc5f15e03f3d3d8fd889670ecde2c66a2e4d2dd9db80733c05c1d90c8a248",
    "tools/dockerfile/test/csharp_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_debian11_x64@sha256:b2e5c47d986312ea0850e2f2e696b45d23ee0aabceea161d31e28559e19ec4a5",
    "tools/dockerfile/test/cxx_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_alpine_x64@sha256:f2019edf9f2afd5042567f11afb1aa78a789fc9acdcce5ee0c14cc11f6830ed7",
    "tools/dockerfile/test/cxx_clang_17_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_clang_17_x64@sha256:05c948d794b7b4cf1b3c45106a1332b80808c7cd7f56aeb9a8ece63641f3d41d",
    "tools/dockerfile/test/cxx_clang_6_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_clang_6_x64@sha256:8e9ddd6c0f3d04c1bf9370cc59712a4e5883f68f307643a9b6dcb2dbd678b579",
    "tools/dockerfile/test/cxx_debian11_openssl102_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_openssl102_x64@sha256:3bae65e56c756c491dfc4b02cff554ae3c4edd9d366d0d05d27e429b59a01b0f",
    "tools/dockerfile/test/cxx_debian11_openssl111_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_openssl111_x64@sha256:63f2cd5ae453aa2a850fc59b9ec8e8a865e63d9f99a2b796de65669f3bf21275",
    "tools/dockerfile/test/cxx_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_x64@sha256:ecd1fbc04423ac9c667a3fbd985a9530e9a4387db372e22229a4d9d77034f4c3",
    "tools/dockerfile/test/cxx_debian11_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_x86@sha256:cba4b92ff05bc51c0668bfce696d4a826728f4c61163b6d6107685cd83098b15",
    "tools/dockerfile/test/cxx_debian12_openssl309_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian12_openssl309_x64@sha256:a3f1242283eb5988e4aefede8af64db6f4bfea0d2875610cf55560abeb60563e",
    "tools/dockerfile/test/cxx_gcc_12_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_gcc_12_x64@sha256:bbdfe66f27b964f9bfd526646b94a19d904fea52bdb244f32fd4355cc8c4551f",
    "tools/dockerfile/test/cxx_gcc_8_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_gcc_8_x64@sha256:a12780fc969d6856211bb80d85de22198bcf0b2f325d1f2e5cc2d779b41ee919",
    "tools/dockerfile/test/php73_zts_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php73_zts_debian11_x64@sha256:bc221d435086d92b2482020214ee70814c569273f8d0cb577a0247e82d598a5f",
    "tools/dockerfile/test/php7_debian11_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php7_debian11_arm64@sha256:7ee21f253a2ddd255f4f6779cd19818eec6524e78b0bf0a7765339e4aa7347c3",
    "tools/dockerfile/test/php7_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php7_debian11_x64@sha256:302c06c5dbffb97dd5540d758a8ce849269527bb7d1c3885af0b956f8f33c49e",
    "tools/dockerfile/test/python_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_alpine_x64@sha256:75fa424f2dae683422a5875d64911d9abf06c31e944401d240666d06f83de573",
    "tools/dockerfile/test/python_debian11_default_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_debian11_default_arm64@sha256:fccca33a655c7aa89dd7ebd9492cbcc1f636bd2a004cd939d1982cfce3d68326",
    "tools/dockerfile/test/python_debian11_default_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_debian11_default_x64@sha256:a956ff4bfbfa4fc6a00c7113f2dada7ce8cf4011f236f07197732981875d6519",
    "tools/dockerfile/test/rbe_ubuntu2004.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rbe_ubuntu2004@sha256:d3951aeadf43e3bee6adc5b86d26cdaf0b9d1b5baf790d7b2530d1c197adc9f8",
    "tools/dockerfile/test/ruby_debian11_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_arm64@sha256:d2e79919b2e2d4cc36a29682ecb5170641df4fb506cfb453978ffdeb8a841bd9",
    "tools/dockerfile/test/ruby_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64@sha256:f8fc0ec22065278e5bc02ad7f9a68191e46d083035b3a90ed587561dba9c58c5",
    "tools/dockerfile/test/sanity.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/sanity@sha256:f9f5bdecfb8ea805b697e55b64a64827c683b507b3cbcc683e2f0101c9bc1643",
}
