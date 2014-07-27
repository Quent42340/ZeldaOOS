
@{{BLOCK(link)

@=======================================================================
@
@	link, 64x32@4, 
@	Transparent color : 0F,F0,FF
@	+ palette 256 entries, not compressed
@	+ 32 tiles Metatiled by 2x2 not compressed
@	Total size: 512 + 1024 = 1536
@
@	Time-stamp: 2014-07-27, 00:45:02
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.12
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global linkTiles		@ 1024 unsigned chars
	.hidden linkTiles
linkTiles:
	.word 0x11100000,0x33210000,0x11211000,0x33113100,0x11313100,0x11113100,0x11122100,0x31331000
	.word 0x00000011,0x00000122,0x00011222,0x00131233,0x00131311,0x00131111,0x00122111,0x00013313
	.word 0x31321000,0x33212100,0x11112310,0x22211310,0x33321100,0x21111000,0x13321100,0x11111000
	.word 0x00012313,0x00121233,0x00121111,0x00123312,0x00013313,0x00001122,0x00011111,0x00001111
	.word 0x11100000,0x22210000,0x33221000,0x22122100,0x11312210,0x12312210,0x13312100,0x13311000
	.word 0x00000011,0x00001123,0x00013312,0x01112331,0x00111233,0x00001112,0x00113131,0x00133133
	.word 0x13210000,0x12110000,0x11210000,0x31221000,0x31221000,0x11111000,0x33310000,0x11111000
	.word 0x00012333,0x00001222,0x00001111,0x00001213,0x00001313,0x00001211,0x00001113,0x00011111

	.word 0x11000000,0x32110000,0x21331000,0x13321110,0x33211100,0x21110000,0x13131100,0x33133100
	.word 0x00000111,0x00001222,0x00012233,0x00122122,0x01221311,0x01221321,0x00121331,0x00011331
	.word 0x33321000,0x22210000,0x11110000,0x31210000,0x31310000,0x11210000,0x31110000,0x11111000
	.word 0x00001231,0x00001121,0x00001211,0x00012213,0x00012213,0x00011111,0x00001333,0x00011111
	.word 0x11000000,0x11100000,0x33100000,0x11311000,0x32113100,0x32213100,0x21213100,0x22112100
	.word 0x00000001,0x00000011,0x00000133,0x00011311,0x00131123,0x00131223,0x00131223,0x00121223
	.word 0x22111000,0x22121000,0x22123100,0x11213100,0x33321000,0x22211000,0x11111000,0x11110000
	.word 0x00011122,0x00121212,0x00121221,0x00112322,0x00012233,0x00011122,0x00113311,0x00011111

	.word 0x11000000,0x22100000,0x22211000,0x33213100,0x11313100,0x11113100,0x11122100,0x31331000
	.word 0x00000111,0x00001233,0x00011211,0x00131133,0x00131311,0x00131111,0x00122111,0x00013313
	.word 0x31321000,0x33212100,0x11112100,0x21332100,0x31331000,0x22110000,0x11111000,0x11110000
	.word 0x00012313,0x00121233,0x01321111,0x01311222,0x00112333,0x00011112,0x00112331,0x00011111
	.word 0x00000000,0x11110000,0x32221100,0x23322210,0x22122210,0x11312210,0x12312100,0x13312100
	.word 0x00000000,0x00000011,0x00101123,0x00113312,0x00112331,0x00011233,0x00001112,0x00113131
	.word 0x13311000,0x13210000,0x11110000,0x12211000,0x12213100,0x22113100,0x11133100,0x11111110
	.word 0x00133133,0x00012333,0x00001111,0x00000133,0x00000133,0x00001111,0x00013333,0x00011111

	.word 0x00000000,0x11000000,0x32110100,0x21331100,0x13321100,0x33211000,0x21110000,0x13131100
	.word 0x00000000,0x00001111,0x00112223,0x01222332,0x01222122,0x01221311,0x00121321,0x00121331
	.word 0x33133100,0x33321000,0x11110000,0x33100000,0x33100000,0x11110000,0x33331000,0x11111000
	.word 0x00011331,0x00001231,0x00001111,0x00011221,0x00131221,0x00131122,0x00133111,0x01111111
	.word 0x10000000,0x11000000,0x33100000,0x11311000,0x32113100,0x32213100,0x32213100,0x32212100
	.word 0x00000011,0x00000111,0x00000133,0x00011311,0x00131123,0x00131223,0x00131212,0x00121122
	.word 0x22111000,0x21212100,0x12212100,0x22321100,0x33221000,0x22111000,0x11331100,0x11111000
	.word 0x00011122,0x00012122,0x00132122,0x00131211,0x00012333,0x00011222,0x00011111,0x00001111

	.section .rodata
	.align	2
	.global linkPal		@ 512 unsigned chars
	.hidden linkPal
linkPal:
	.hword 0x7C1F,0x0000,0x22A2,0x475F,0x0000,0x0000,0x0000,0x0000
	.hword 0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421
	.hword 0x0842,0x0842,0x0842,0x0842,0x0842,0x0842,0x0842,0x0842
	.hword 0x0C63,0x0C63,0x0C63,0x0C63,0x0C63,0x0C63,0x0C63,0x0C63
	.hword 0x1084,0x1084,0x1084,0x1084,0x1084,0x1084,0x1084,0x1084
	.hword 0x14A5,0x14A5,0x14A5,0x14A5,0x14A5,0x14A5,0x14A5,0x14A5
	.hword 0x18C6,0x18C6,0x18C6,0x18C6,0x18C6,0x18C6,0x18C6,0x18C6
	.hword 0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7

	.hword 0x2108,0x2108,0x2108,0x2108,0x2108,0x2108,0x2108,0x2108
	.hword 0x2529,0x2529,0x2529,0x2529,0x2529,0x2529,0x2529,0x2529
	.hword 0x294A,0x294A,0x294A,0x294A,0x294A,0x294A,0x294A,0x294A
	.hword 0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B
	.hword 0x318C,0x318C,0x318C,0x318C,0x318C,0x318C,0x318C,0x318C
	.hword 0x35AD,0x35AD,0x35AD,0x35AD,0x35AD,0x35AD,0x35AD,0x35AD
	.hword 0x39CE,0x39CE,0x39CE,0x39CE,0x39CE,0x39CE,0x39CE,0x39CE
	.hword 0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF

	.hword 0x4210,0x4210,0x4210,0x4210,0x4210,0x4210,0x4210,0x4210
	.hword 0x4631,0x4631,0x4631,0x4631,0x4631,0x4631,0x4631,0x4631
	.hword 0x4A52,0x4A52,0x4A52,0x4A52,0x4A52,0x4A52,0x4A52,0x4A52
	.hword 0x4E73,0x4E73,0x4E73,0x4E73,0x4E73,0x4E73,0x4E73,0x4E73
	.hword 0x5294,0x5294,0x5294,0x5294,0x5294,0x5294,0x5294,0x5294
	.hword 0x56B5,0x56B5,0x56B5,0x56B5,0x56B5,0x56B5,0x56B5,0x56B5
	.hword 0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6
	.hword 0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7

	.hword 0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,0x6318
	.hword 0x6739,0x6739,0x6739,0x6739,0x6739,0x6739,0x6739,0x6739
	.hword 0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A
	.hword 0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B
	.hword 0x739C,0x739C,0x739C,0x739C,0x739C,0x739C,0x739C,0x739C
	.hword 0x77BD,0x77BD,0x77BD,0x77BD,0x77BD,0x77BD,0x77BD,0x77BD
	.hword 0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE
	.hword 0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF

@}}BLOCK(link)
