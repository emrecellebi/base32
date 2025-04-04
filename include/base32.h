#ifndef BASE32_H
#define BASE32_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BASE32_LENGTH(inlen) ((((inlen) + 4) / 5) * 8)

struct base32_decode_context
{
	unsigned int i;
	char buf[8];
};

extern bool isbase32(char ch);
extern void base32_encode(const char* in, size_t inlen, char* out, size_t outlen);
extern void base32_decode_ctx_init(struct base32_decode_context* ctx);
extern bool base32_decode_ctx(struct base32_decode_context* ctx, const char* in, size_t inlen, char* out, size_t* outlen);
extern bool base32_decode_alloc_ctx(struct base32_decode_context* ctx, const char* in, size_t inlen, char** out, size_t* outlen);
extern size_t base32_encode_alloc(const char* in, size_t inlen, char** out);

#ifdef __cplusplus
}
#endif

#endif /* BASE32_H */