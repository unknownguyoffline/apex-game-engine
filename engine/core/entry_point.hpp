#pragma once

void *operator new(unsigned long size);
void operator delete(void *pointer) noexcept;

int main();
