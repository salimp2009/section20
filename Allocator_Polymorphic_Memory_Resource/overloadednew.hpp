#pragma once

static int count{0};

 void* operator new(std::size_t size) 
{
    ++count;
    printf("Allocating: %lu\n count= %d\n", size * sizeof(char), count);
    return malloc(size);
}

void operator delete(void* p, std::size_t size) noexcept
{
    --count;
    printf("De-allocating: size= %lu\n", size * sizeof(char) ); 
    free(p);
}