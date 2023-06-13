emcc -o web/add.js \
czoko.cpp \
-Wall -std=c++20 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I. \
-I ~/CLionProjects/bandit/vendor/raylib/src \
-I ~/CLionProjects/bandit/vendor/raylib/src/external -L. \
-L ~/CLionProjects/bandit/vendor/raylib/src \
-s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -sALLOW_MEMORY_GROWTH -s FORCE_FILESYSTEM=1 \
~/CLionProjects/bandit/vendor/raylib/src/web/libraylib.a -DPLATFORM_WEB \
-s 'EXPORTED_FUNCTIONS=["_free","_malloc","_main"]' \
-s EXPORTED_RUNTIME_METHODS=ccall,cwrap \
-s ENVIRONMENT=worker \
-s MODULARIZE=1 \
-sASSERTIONS
