## 🚀 Getting Started

### 1️⃣ Clone the Repository

git clone 
cd Code

### 2️⃣ Build

Using CMake:

cmake -B build
cmake --build build

Or open in STM32CubeIDE directly.

### 3️⃣ Flash

Use ST-Link:

st-flash write build/firmware.bin 0x8000000
