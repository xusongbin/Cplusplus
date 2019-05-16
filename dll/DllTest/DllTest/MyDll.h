#pragma once

#define DLLEXPORT extern "C" __declspec(dllexport)

DLLEXPORT int myadd(int a, int b);