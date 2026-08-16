#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

/* 
 * Orijinal printf ile ft_printf'i kapıştıran acımasız makro.
 * Hem ekrana basılan karakterleri hem de return değerlerini kıyaslar.
 */
#define BATTLE_TEST(test_name, fmt, ...) \
	do { \
		int ret_orig, ret_ft; \
		printf("\n========== %s ==========\n", test_name); \
		printf("Original  : ["); \
		ret_orig = printf(fmt, ##__VA_ARGS__); \
		printf("] -> Uzunluk: %d\n", ret_orig); \
		printf("ft_printf : ["); \
		fflush(stdout); \
		ret_ft = ft_printf(fmt, ##__VA_ARGS__); \
		printf("] -> Uzunluk: %d\n", ret_ft); \
		if (ret_orig == ret_ft) \
			printf("\033[0;32m[BASARILI]\033[0m Return degerleri esit.\n"); \
		else \
			printf("\033[0;31m[HATA]\033[0m Return degerleri farkli! (Orijinal: %d, ft: %d)\n", ret_orig, ret_ft); \
	} while (0)

int	main(void)
{
	printf("\033[0;36m\n--- FT_PRINTF PATLATMA TESTLERI BASLIYOR ---\n\033[0m");

	// 1. Temel String ve Karakter Testleri (NULL patlatıcılar)
	BATTLE_TEST("Normal String", "Merhaba %s", "Dunya");
	BATTLE_TEST("Bos String", "Bos string: %s", "");
	BATTLE_TEST("NULL String", "Null string testi: %s", (char *)NULL);
	BATTLE_TEST("Karakter '0'", "Karakter: %c", '0');
	BATTLE_TEST("Karakter 0 (Non-printable)", "Gorunmez char: %c", 0);

	// 2. Sayısal Sınır Testleri (Integer Overflow/Underflow)
	BATTLE_TEST("Sifir Degeri", "Sifir: %d ve %i", 0, 0);
	BATTLE_TEST("Negatif Sayi", "Negatif: %d", -42);
	BATTLE_TEST("INT MAX", "Maksimum Integer: %d", INT_MAX);
	BATTLE_TEST("INT MIN (Cok Can Yakar)", "Minimum Integer: %d", INT_MIN);

	// 3. Unsigned Sınır Testleri
	BATTLE_TEST("Unsigned Sifir", "Unsigned sifir: %u", 0);
	BATTLE_TEST("Unsigned MAX", "Unsigned maksimum: %u", UINT_MAX);
	BATTLE_TEST("Unsigned Negatif (Tersine donme)", "Eksi bir: %u", -1);

	// 4. Hexadecimal Testleri
	BATTLE_TEST("Hex Sifir", "Kucuk hex: %x, Buyuk hex: %X", 0, 0);
	BATTLE_TEST("Hex Normal", "Hex: %x ve %X", 255, 255);
	BATTLE_TEST("Hex UINT MAX", "Max Hex: %x, %X", UINT_MAX, UINT_MAX);

	// 5. Pointer Testleri (Genelde macOS ve Linux arasinda farklilik gosterir)
	int x = 42;
	BATTLE_TEST("Gecerli Pointer", "Pointer adresi: %p", &x);
	BATTLE_TEST("NULL Pointer", "Null pointer: %p", NULL);
	BATTLE_TEST("Long Min Pointer", "Garip pointer: %p", (void *)LONG_MIN);

	// 6. Lanetli Yüzde Testleri (Sonsuzluk ve Boşluklar)
	BATTLE_TEST("Cift Yuzde", "Yuzde isareti: %%");
	BATTLE_TEST("Pek Cok Yuzde", "Coklu yuzde: %%%%%%");
	
	// Not: Dangling '%' (sonda tek kalan yüzde) C standartlarında tanımsız davranıştır (Undefined Behavior).
	// Compiler '-Wformat' uyarısı verebilir, o yüzden test ederken flag'leri göz önünde bulundur.
	printf("\n========== Dangling Yuzde (%%) ==========\n");
	int ret_orig = printf("Sonda tek yuzde: %");
	printf("\nOriginal Return: %d\n", ret_orig);
	int ret_ft = ft_printf("Sonda tek yuzde: %");
	printf("\nft_printf Return: %d\n", ret_ft);
	if (ret_orig == ret_ft)
		printf("\033[0;32m[BASARILI]\033[0m Return degerleri esit.\n");
	else
		printf("\033[0;31m[HATA]\033[0m Return degerleri farkli!\n");

	// 7. Karmaşık Kombo Testi (Gerçek hayat senaryosu)
	BATTLE_TEST("Kombo Test", "Char: %c, Str: %s, Int: %d, Hex: %x, Yuzde: %%", 'X', "Test", -42, 255);

	printf("\033[0;36m\n--- TESTLER TAMAMLANDI ---\n\033[0m\n");
	return (0);
}