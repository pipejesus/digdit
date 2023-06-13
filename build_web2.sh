emcc -o web/index.html \
main.cpp src/StarBackground.cpp \
-Wall -std=c++20 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I. \
-I ~/CLionProjects/bandit/vendor/raylib/src \
-I ~/CLionProjects/bandit/vendor/raylib/src/external -L. \
-L ~/CLionProjects/bandit/vendor/raylib/src \
-s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -sALLOW_MEMORY_GROWTH -s FORCE_FILESYSTEM=1 \
--preload-file models-final --preload-file shaders \
--shell-file web-shells/resizable-shell.html \
~/CLionProjects/bandit/vendor/raylib/src/web/libraylib.a -DPLATFORM_WEB \
-s 'EXPORTED_FUNCTIONS=["_free","_malloc","_main","_onResize"]' \
-s EXPORTED_RUNTIME_METHODS=ccall,cwrap \
-s EXPORT_ES6=1 -s MODULARIZE=1 \
-s EXPORT_NAME="'PtackModule'" \
-sASSERTIONS
