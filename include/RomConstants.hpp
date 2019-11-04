#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#ifndef ROM_CONSTANTS_HPP
#define ROM_CONSTANTS_HPP

#include <map>
#include <string>

namespace goober {
    static const uint16_t ROM_BANK_SIZE = 16384;

	/**
	 * Map containing all possible cart types mapped to their in-ROM hex values.
	 */
	static std::map<uint8_t, std::string> CART_TYPE_MAP {
		{0x00,"rom_only"},
		{0x01,"mbc1"},
		{0x02,"mbc1+ram"},
		{0x03,"mbc1+ram+bat"},
		{0x05,"mbc2"},
		{0x06,"mbc2+bat"},
		{0x08,"rom+ram"},
		{0x09,"rom+ram+bat"},
		{0x0B,"mmm01"},
		{0x0C,"mmm01+ram"},
		{0x0D,"mmm01+ram+bat"},
		{0x0F,"mbc3+timer+bat"},
		{0x10,"mbc3+timer+ram+bat"},
		{0x11,"mbc3"},
		{0x12,"mbc3+ram"},
		{0x13,"mbc3+ram+bat"},
		{0x19,"mbc5"},
		{0x1A,"mbc5+ram"},
		{0x1B,"mbc5+ram+bat"},
		{0x1C,"mbc5+rumble"},
		{0x1D,"mbc5+rumble+ram"},
		{0x1E,"mbc5+rumble+ram+bat"},
		{0x20,"mbc6"},
		{0x22,"mbc7+sensor+rumble+ram+bat"},
		{0xFC,"pocket_cam"},
		{0xFD,"bandai_tama5"},
		{0xFE,"HuC3"},
		{0xFF,"HuC1+ram+bat"},
	};

	/**
	 * Map containing all possible licensees for the "old" mapping system mapped to their in-ROM hex values.
	 */
	static std::map<uint8_t, std::string> OLD_LICENSEES_MAP {
		{0x00,"none"},
		{0x01,"nintendo"},
		{0x08,"capcom"},
		{0x09,"hot-b"},
		{0x0A,"jaleco"},
		{0x0B,"coconuts"},
		{0x0C,"elite systems"},
		{0x13,"electronic arts"},
		{0x18,"hudsonsoft"},
		{0x19,"itc entertainment"},
		{0x1A,"yanoman"},
		{0x1D,"clary"},
		{0x1F,"virgin"},
		{0x20,"KSS"},
		{0x24,"pcm complete"},
		{0x25,"san-x"},
		{0x28,"kotobuki systems"},
		{0x29,"pcm complete"},
		{0x30,"infogrames"},
		{0x31,"nintendo"},
		{0x32,"bandai"},
		{0x33,"GBC_CODE"},
		{0x34,"konami"},
		{0x35,"hector"},
		{0x38,"Capcom"},
		{0x39,"Banpresto"},
		{0x3C,"entertainment i..."},
		{0x3E,"gremiln"},
		{0x41,"Ubisoft"},
		{0x42,"Atlus"},
		{0x44,"Malibu"},
		{0x46,"angel"},
		{0x47,"spectrum holoby"},
		{0x49,"irem"},
		{0x4A,"virgin"},
		{0x4D,"malibu"},
		{0x4F,"u.s. gold"},
		{0x50,"absolute"},
		{0x51,"acclaim"},
		{0x52,"activision"},
		{0x53,"american sammy"},
		{0x54,"gametek"},
		{0x55,"park place"},
		{0x56,"ljn"},
		{0x57,"matchbox"},
		{0x59,"milton bradley"},
		{0x5A,"mindscape"},
		{0x5B,"romstar"},
		{0x5C,"naxat soft"},
		{0x5D,"tradewest"},
		{0x60,"titus"},
		{0x61,"virgin"},
		{0x67,"ocean"},
		{0x69,"electronic arts"},
		{0x6E,"elite systems"},
		{0x6F,"electro brain"},
		{0x70,"Infogrammes"},
		{0x71,"Interplay"},
		{0x72,"broderbund"},
		{0x73,"sculptured soft"},
		{0x75,"the sales curve"},
		{0x78,"t*hq"},
		{0x79,"accolade"},
		{0x7A,"triffix entertainment"},
		{0x7C,"microprose"},
		{0x7F,"kemco"},
		{0x80,"misawa entertainment"},
		{0x83,"lozc"},
		{0x86,"tokuma shoten intermedia"},
		{0x8B,"bullet-proof software"},
		{0x8C,"vic tokai"},
		{0x8E,"ape"},
		{0x8F,"i'max"},
		{0x91,"chun soft"},
		{0x92,"video system"},
		{0x93,"tsuburava"},
		{0x95,"varie"},
		{0x96,"yonezawa/s'pal"},
		{0x97,"kaneko"},
		{0x99,"ac"},
		{0x9A,"nihon bussan"},
		{0x9B,"Tecmo"},
		{0x9C,"imagineer"},
		{0x9D,"Banpresto"},
		{0x9F,"nova"},
		{0xA1,"Hori electric"},
		{0xA2,"Bandai"},
		{0xA4,"Konami"},
		{0xA6,"kawada"},
		{0xA7,"takara"},
		{0xA9,"technos japan"},
		{0xAA,"broderbund"},
		{0xAC,"Toei animation"},
		{0xAD,"toho"},
		{0xAF,"Namco"},
		{0xB0,"Acclaim"},
		{0xB1,"ascii or nexoft"},
		{0xB2,"Bandai"},
		{0xB4,"Enix"},
		{0xB6,"HAL"},
		{0xB7,"SNK"},
		{0xB9,"pony canyon"},
		{0xBA,"culture brain"},
		{0xBB,"Sunsoft"},
		{0xBD,"Sony imagesoft"},
		{0xBF,"sammy"},
		{0xC0,"Taito"},
		{0xC2,"Kemco"},
		{0xC3,"Squaresoft"},
		{0xC4,"tokuma shoten intermedia"},
		{0xC5,"data east"},
		{0xC6,"tonkin house"},
		{0xC8,"koei"},
		{0xC9,"ufl"},
		{0xCA,"ultra"},
		{0xCB,"vap"},
		{0xCC,"use"},
		{0xCD,"meldac"},
		{0xCE,"pony canyon"},
		{0xCF,"angel"},
		{0xD0,"Taito"},
		{0xD1,"sofel"},
		{0xD2,"quest"},
		{0xD3,"sigma enterprises"},
		{0xD4,"ask kodansha"},
		{0xD6,"naxat soft"},
		{0xD7,"copya systems"},
		{0xD9,"Banpresto"},
		{0xDA,"tomy"},
		{0xDB,"ljn"},
		{0xDD,"ncs"},
		{0xDE,"human"},
		{0xDF,"altron"},
		{0xE0,"jaleco"},
		{0xE1,"towachiki"},
		{0xE2,"uutaka"},
		{0xE3,"varie"},
		{0xE5,"epoch"},
		{0xE7,"athena"},
		{0xE8,"asmik"},
		{0xE9,"natsume"},
		{0xEA,"king records"},
		{0xEB,"atlus"},
		{0xEC,"Epic/Sony records"},
		{0xEE,"igs"},
		{0xF0,"a wave"},
		{0xF3,"extreme entertainment"},
		{0xFF,"ljn"},
	};

	/**
	 * Map containing all possible numbers of ROM banks based on hex value.
	 */
	static std::map<uint8_t, uint16_t> ROM_BANK_MAP {
		{0x00, 0}, {0x01, 4}, {0x02, 8}, {0x03, 16}, {0x04, 32},
		{0x05, 64}, {0x06, 128}, {0x07, 256}, {0x08, 512},
		{0x52, 72}, {0x53, 80}, {0x54, 96}
	};

	/**
	 * Map for determining how much RAM is needed.
	 */
	static std::map<uint8_t, uint8_t> RAM_SIZE_MAP {
		{0x00, 0}, {0x01, 2}, {0x02, 8}, {0x03, 32}, {0x04, 128}, {0x05, 64}
	};

	/**
	 * Map for determining if the ROM only works in GameBoy Color mode
	 */
	static std::map<uint8_t, bool> CGB_FLAG_MAP {
		{0x80, false}, {0xC0, true}
	};

	/**
	 * Map for determining if the ROM has special support for the Super GameBoy
	 */
	static std::map< uint8_t, bool> SGB_FLAG_MAP {
		{0x00, false}, {0x30, true}
	};

	/**
	 * Map for determining if the ROM is region-locked to Japan
	 */
	static std::map<uint8_t, bool> DEST_CODE_MAP {
		{0x00, true}, {0x01, false}
	};
};

#endif
#pragma clang diagnostic pop