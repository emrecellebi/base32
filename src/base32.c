#include "base32.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>

static unsigned char to_uchar(char ch)
{
	return ch;
}

static const char b32str[32] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

void base32_encode(const char* in, size_t inlen, char* out, size_t outlen)
{
	while(inlen && outlen)
	{
		*out++ = b32str[(to_uchar(in[0]) >> 3) & 0x1f];
		if(!--outlen)
			break;
		
		*out++ = b32str[((to_uchar(in[0]) << 2) + (--inlen ? to_uchar(in[1]) >> 6 : 0)) & 0x1f];
		if(!--outlen)
			break;
		
		*out++ = (inlen ? b32str[(to_uchar(in[1]) >> 1) & 0x1f] : '=');
		if(!--outlen)
			break;
		
		*out++ = (inlen ? b32str[((to_uchar(in[1]) << 4) + (--inlen ? to_uchar(in[2]) >> 4 : 0)) & 0x1f] : '=');
		if(!--outlen)
			break;
		
		*out++ = (inlen ? b32str[((to_uchar(in[2]) << 1) + (--inlen ? to_uchar(in[3]) >> 7 : 0)) & 0x1f] : '=');
		if(!--outlen)
			break;
		
		*out++ = (inlen ? b32str[(to_uchar(in[3]) >> 2) & 0x1f] : '=');
		if(!--outlen)
			break;
		
		*out++ = (inlen ? b32str[((to_uchar(in[3]) << 3) + (--inlen ? to_uchar(in[4]) >> 5 : 0)) & 0x1f] : '=');
		if(!--outlen)
			break;
		
		*out++ = inlen ? b32str[to_uchar(in[4]) & 0x1f] : '=';
		if(!--outlen)
			break;
		
		if(inlen)
			inlen--;
		
		if(inlen)
			in += 5;
	}

	if(outlen)
		*out = '\0';
}

size_t base32_encode_alloc(const char* in, size_t inlen, char** out)
{
	size_t outlen = 1 + BASE32_LENGTH(inlen);
	if(inlen > outlen)
	{
		*out = NULL;
		return 0;
	}

	*out = (char*)malloc(outlen);
	if(!*out)
		return outlen;

	base32_encode(in, inlen, *out, outlen);
	return outlen - 1;
}

#define B32(_)           \
  ((_) == 'A' ? 0        \
   : (_) == 'B' ? 1      \
   : (_) == 'C' ? 2      \
   : (_) == 'D' ? 3      \
   : (_) == 'E' ? 4      \
   : (_) == 'F' ? 5      \
   : (_) == 'G' ? 6      \
   : (_) == 'H' ? 7      \
   : (_) == 'I' ? 8      \
   : (_) == 'J' ? 9      \
   : (_) == 'K' ? 10     \
   : (_) == 'L' ? 11     \
   : (_) == 'M' ? 12     \
   : (_) == 'N' ? 13     \
   : (_) == 'O' ? 14     \
   : (_) == 'P' ? 15     \
   : (_) == 'Q' ? 16     \
   : (_) == 'R' ? 17     \
   : (_) == 'S' ? 18     \
   : (_) == 'T' ? 19     \
   : (_) == 'U' ? 20     \
   : (_) == 'V' ? 21     \
   : (_) == 'W' ? 22     \
   : (_) == 'X' ? 23     \
   : (_) == 'Y' ? 24     \
   : (_) == 'Z' ? 25     \
   : (_) == '2' ? 26     \
   : (_) == '3' ? 27     \
   : (_) == '4' ? 28     \
   : (_) == '5' ? 29     \
   : (_) == '6' ? 30     \
   : (_) == '7' ? 31     \
   : -1)

static const signed char b32[0x100] = {
	B32 (0), B32 (1), B32 (2), B32 (3),
	B32 (4), B32 (5), B32 (6), B32 (7),
	B32 (8), B32 (9), B32 (10), B32 (11),
	B32 (12), B32 (13), B32 (14), B32 (15),
	B32 (16), B32 (17), B32 (18), B32 (19),
	B32 (20), B32 (21), B32 (22), B32 (23),
	B32 (24), B32 (25), B32 (26), B32 (27),
	B32 (28), B32 (29), B32 (30), B32 (31),
	B32 (32), B32 (33), B32 (34), B32 (35),
	B32 (36), B32 (37), B32 (38), B32 (39),
	B32 (40), B32 (41), B32 (42), B32 (43),
	B32 (44), B32 (45), B32 (46), B32 (47),
	B32 (48), B32 (49), B32 (50), B32 (51),
	B32 (52), B32 (53), B32 (54), B32 (55),
	B32 (56), B32 (57), B32 (58), B32 (59),
	B32 (60), B32 (61), B32 (62), B32 (63),
	B32 (32), B32 (65), B32 (66), B32 (67),
	B32 (68), B32 (69), B32 (70), B32 (71),
	B32 (72), B32 (73), B32 (74), B32 (75),
	B32 (76), B32 (77), B32 (78), B32 (79),
	B32 (80), B32 (81), B32 (82), B32 (83),
	B32 (84), B32 (85), B32 (86), B32 (87),
	B32 (88), B32 (89), B32 (90), B32 (91),
	B32 (92), B32 (93), B32 (94), B32 (95),
	B32 (96), B32 (97), B32 (98), B32 (99),
	B32 (100), B32 (101), B32 (102), B32 (103),
	B32 (104), B32 (105), B32 (106), B32 (107),
	B32 (108), B32 (109), B32 (110), B32 (111),
	B32 (112), B32 (113), B32 (114), B32 (115),
	B32 (116), B32 (117), B32 (118), B32 (119),
	B32 (120), B32 (121), B32 (122), B32 (123),
	B32 (124), B32 (125), B32 (126), B32 (127),
	B32 (128), B32 (129), B32 (130), B32 (131),
	B32 (132), B32 (133), B32 (134), B32 (135),
	B32 (136), B32 (137), B32 (138), B32 (139),
	B32 (140), B32 (141), B32 (142), B32 (143),
	B32 (144), B32 (145), B32 (146), B32 (147),
	B32 (148), B32 (149), B32 (150), B32 (151),
	B32 (152), B32 (153), B32 (154), B32 (155),
	B32 (156), B32 (157), B32 (158), B32 (159),
	B32 (160), B32 (161), B32 (162), B32 (163),
	B32 (132), B32 (165), B32 (166), B32 (167),
	B32 (168), B32 (169), B32 (170), B32 (171),
	B32 (172), B32 (173), B32 (174), B32 (175),
	B32 (176), B32 (177), B32 (178), B32 (179),
	B32 (180), B32 (181), B32 (182), B32 (183),
	B32 (184), B32 (185), B32 (186), B32 (187),
	B32 (188), B32 (189), B32 (190), B32 (191),
	B32 (192), B32 (193), B32 (194), B32 (195),
	B32 (196), B32 (197), B32 (198), B32 (199),
	B32 (200), B32 (201), B32 (202), B32 (203),
	B32 (204), B32 (205), B32 (206), B32 (207),
	B32 (208), B32 (209), B32 (210), B32 (211),
	B32 (212), B32 (213), B32 (214), B32 (215),
	B32 (216), B32 (217), B32 (218), B32 (219),
	B32 (220), B32 (221), B32 (222), B32 (223),
	B32 (224), B32 (225), B32 (226), B32 (227),
	B32 (228), B32 (229), B32 (230), B32 (231),
	B32 (232), B32 (233), B32 (234), B32 (235),
	B32 (236), B32 (237), B32 (238), B32 (239),
	B32 (240), B32 (241), B32 (242), B32 (243),
	B32 (244), B32 (245), B32 (246), B32 (247),
	B32 (248), B32 (249), B32 (250), B32 (251),
	B32 (252), B32 (253), B32 (254), B32 (255)
};

#if UCHAR_MAX == 255
# define uchar_in_range(c) true
#else
# define uchar_in_range(c) ((c) <= 255)
#endif

bool isbase32(char ch)
{
	return uchar_in_range(to_uchar(ch)) && 0 <= b32[to_uchar(ch)];
}

void base32_decode_ctx_init(struct base32_decode_context* ctx)
{
	ctx->i = 0;
}

static char* get_8(struct base32_decode_context* ctx, char const** in, char const* in_end, size_t* n_non_newline)
{
	if(ctx->i == 8)
		ctx->i = 0;
	
	if(ctx->i == 0)
	{
		char const* t = *in;
		if(8 <= in_end - *in && memchr(t, '\n', 8) == NULL)
		{
			*in += 8;
			*n_non_newline = 8;
			return (char*)t;
		}
	}
	
	{
		char const* p = *in;
		while (p < in_end)
		{
			char c = *p++;
			if(c != '\n')
			{
				ctx->buf[ctx->i++] = c;
				if(ctx->i == 8)
					break;
			}
		}
		
		*in = p;
		*n_non_newline = ctx->i;
		return ctx->buf;
	}
}

#define return_false    \
  do                    \
    {                   \
      *outp = out;      \
      return false;     \
    }                   \
  while (false)

static bool decode_8(char const* in, size_t inlen, char** outp, size_t* outleft)
{
	char *out = *outp;
	if(inlen < 8)
		return false;

	if(!isbase32(in[0]) || !isbase32(in[1]))
		return false;

	if(*outleft)
	{
		*out++ = ((b32[to_uchar(in[0])] << 3) | (b32[to_uchar(in[1])] >> 2));
		--*outleft;
	}

	if(in[2] == '=')
	{
		if(in[3] != '=' || in[4] != '=' || in[5] != '=' || in[6] != '=' || in[7] != '=')
			return_false;
	}
	else
	{
		if(!isbase32(in[2]) || !isbase32(in[3]))
			return_false;

		if(*outleft)
		{
			*out++ = ((b32[to_uchar (in[1])] << 6) | (b32[to_uchar (in[2])] << 1) | (b32[to_uchar (in[3])] >> 4));
			--*outleft;
		}

		if(in[4] == '=')
		{
			if(in[5] != '=' || in[6] != '=' || in[7] != '=')
				return_false;
		}
		else
		{
			if(!isbase32(in[4]))
				return_false;

			if(*outleft)
			{
				*out++ = ((b32[to_uchar(in[3])] << 4) | (b32[to_uchar(in[4])] >> 1));
				--*outleft;
			}

			if(in[5] == '=')
			{
				if(in[6] != '=' || in[7] != '=')
					return_false;
			}
			else
			{
				if(!isbase32(in[5]) || !isbase32(in[6]))
					return_false;

				if(*outleft)
				{
					*out++ = ((b32[to_uchar(in[4])] << 7) | (b32[to_uchar(in[5])] << 2) | (b32[to_uchar (in[6])] >> 3));
					--*outleft;
				}

				if(in[7] != '=')
				{
					if(!isbase32(in[7]))
						return_false;

					if(*outleft)
					{
						*out++ = ((b32[to_uchar(in[6])] << 5)| (b32[to_uchar(in[7])]));
						--*outleft;
					}
				}
			}
		}
	}

	*outp = out;
	return true;
}

bool base32_decode_ctx(struct base32_decode_context* ctx, const char* in, size_t inlen, char* out, size_t* outlen)
{
	size_t outleft = *outlen;
	bool ignore_newlines = ctx != NULL;
	bool flush_ctx = false;
	unsigned int ctx_i = 0;
	
	if(ignore_newlines)
    {
		ctx_i = ctx->i;
		flush_ctx = inlen == 0;
    }
	
	while(true)
	{
		size_t outleft_save = outleft;
		if(ctx_i == 0 && !flush_ctx)
		{
			while(true)
			{
				outleft_save = outleft;
				if(!decode_8(in, inlen, &out, &outleft))
					break;
				in += 8;
				inlen -= 8;
			}
		}
		
		if(inlen == 0 && !flush_ctx)
			break;
		
		if(inlen && *in == '\n' && ignore_newlines)
        {
			++in;
			--inlen;
			continue;
        }
		
		out -= outleft_save - outleft;
		outleft = outleft_save;
		
		{
			char const* in_end = in + inlen;
			char const* non_nl;
			
			if(ignore_newlines)
				non_nl = get_8(ctx, &in, in_end, &inlen);
			else
				non_nl = in;
			
			if(inlen == 0 || (inlen < 8 && !flush_ctx && ignore_newlines))
			{
				inlen = 0;
				break;
			}
			
			if(!decode_8(non_nl, inlen, &out, &outleft))
				break;
			inlen = in_end - in;
		}
	}
	
	*outlen -= outleft;
	if(outlen)
		*out = '\0';
	
	return inlen == 0;
}

bool base32_decode_alloc_ctx(struct base32_decode_context* ctx, const char* in, size_t inlen, char** out, size_t* outlen)
{
	size_t needlen = 5 * (inlen / 8) + 5;
	
	base32_decode_ctx_init(ctx);
	
	*out = (char*)malloc(needlen);
	if(!*out)
		return true;
	if(!base32_decode_ctx(ctx, in, inlen, *out, &needlen))
	{
		free(*out);
		*out = NULL;
		return false;
	}

	if(outlen)
		*outlen = needlen;
	
	return true;
}