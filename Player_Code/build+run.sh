g++ -g main.cpp GstPlayer.cpp -o player++ `pkg-config --cflags --libs gstreamer-1.0` -std=gnu++11
./player++
