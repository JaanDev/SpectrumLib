#pragma once
#include <memory>
#include <unordered_map>
#include "utils.hpp"
#include "Texture.hpp"
#include <filesystem>

NS_SPECTRUM_BEGIN

struct FontRange {
    int startCP; // start codepoint (inclusive)
    int endCP;   // start codepoint (inclusive)

   static FontRange BasicLatin;
   static FontRange BlockElements;
   static FontRange Latin1Supplement;
   static FontRange GeometricShapes;
   static FontRange LatinExtendedA;
   static FontRange MiscellaneousSymbols;
   static FontRange LatinExtendedB;
   static FontRange Dingbats;
   static FontRange IpaExtensions;
   static FontRange MiscellaneousMathematicalSymbolsA;
   static FontRange SpacingModifierLetters;
   static FontRange SupplementalArrowsA;
   static FontRange CombiningDiacriticalMarks;
   static FontRange BraillePatterns;
   static FontRange GreekAndCoptic;
   static FontRange SupplementalArrowsB;
   static FontRange Cyrillic;
   static FontRange MiscellaneousMathematicalSymbolsB;
   static FontRange CyrillicSupplementary;
   static FontRange SupplementalMathematicalOperators;
   static FontRange Armenian;
   static FontRange MiscellaneousSymbolsAndArrows;
   static FontRange Hebrew;
   static FontRange CjkRadicalsSupplement;
   static FontRange Arabic;
   static FontRange KangxiRadicals;
   static FontRange Syriac;
   static FontRange IdeographicDescriptionCharacters;
   static FontRange Thaana;
   static FontRange CjkSymbolsAndPunctuation;
   static FontRange Devanagari;
   static FontRange Hiragana;
   static FontRange Bengali;
   static FontRange Katakana;
   static FontRange Gurmukhi;
   static FontRange Bopomofo;
   static FontRange Gujarati;
   static FontRange HangulCompatibilityJamo;
   static FontRange Oriya;
   static FontRange Kanbun;
   static FontRange Tamil;
   static FontRange BopomofoExtended;
   static FontRange Telugu;
   static FontRange KatakanaPhoneticExtensions;
   static FontRange Kannada;
   static FontRange EnclosedCjkLettersAndMonths;
   static FontRange Malayalam;
   static FontRange CjkCompatibility;
   static FontRange Sinhala;
   static FontRange CjkUnifiedIdeographsExtensionA;
   static FontRange Thai;
   static FontRange YijingHexagramSymbols;
   static FontRange Lao;
   static FontRange CjkUnifiedIdeographs;
   static FontRange Tibetan;
   static FontRange YiSyllables;
   static FontRange Myanmar;
   static FontRange YiRadicals;
   static FontRange Georgian;
   static FontRange HangulSyllables;
   static FontRange HangulJamo;
   static FontRange HighSurrogates;
   static FontRange Ethiopic;
   static FontRange HighPrivateUseSurrogates;
   static FontRange Cherokee;
   static FontRange LowSurrogates;
   static FontRange UnifiedCanadianAboriginalSyllabics;
   static FontRange PrivateUseArea;
   static FontRange Ogham;
   static FontRange CjkCompatibilityIdeographs;
   static FontRange Runic;
   static FontRange AlphabeticPresentationForms;
   static FontRange Tagalog;
   static FontRange ArabicPresentationFormsA;
   static FontRange Hanunoo;
   static FontRange VariationSelectors;
   static FontRange Buhid;
   static FontRange CombiningHalfMarks;
   static FontRange Tagbanwa;
   static FontRange CjkCompatibilityForms;
   static FontRange Khmer;
   static FontRange SmallFormVariants;
   static FontRange Mongolian;
   static FontRange ArabicPresentationFormsB;
   static FontRange Limbu;
   static FontRange HalfwidthAndFullwidthForms;
   static FontRange TaiLe;
   static FontRange Specials;
   static FontRange KhmerSymbols;
   static FontRange LinearBSyllabary;
   static FontRange PhoneticExtensions;
   static FontRange LinearBIdeograms;
   static FontRange LatinExtendedAdditional;
   static FontRange AegeanNumbers;
   static FontRange GreekExtended;
   static FontRange OldItalic;
   static FontRange GeneralPunctuation;
   static FontRange Gothic;
   static FontRange SuperscriptsAndSubscripts;
   static FontRange Ugaritic;
   static FontRange CurrencySymbols;
   static FontRange Deseret;
   static FontRange CombiningDiacriticalMarksForSymbols;
   static FontRange Shavian;
   static FontRange LetterlikeSymbols;
   static FontRange Osmanya;
   static FontRange NumberForms;
   static FontRange CypriotSyllabary;
   static FontRange Arrows;
   static FontRange ByzantineMusicalSymbols;
   static FontRange MathematicalOperators;
   static FontRange MusicalSymbols;
   static FontRange MiscellaneousTechnical;
   static FontRange TaiXuanJingSymbols;
   static FontRange ControlPictures;
   static FontRange MathematicalAlphanumericSymbols;
   static FontRange OpticalCharacterRecognition;
   static FontRange CjkUnifiedIdeographsExtensionB;
   static FontRange EnclosedAlphanumerics;
   static FontRange CjkCompatibilityIdeographsSupplement;
   static FontRange BoxDrawing;
   static FontRange Tags;
};

inline FontRange FontRange::BasicLatin = {0x20, 0x7f};
inline FontRange FontRange::BlockElements = {0x2580, 0x259f};
inline FontRange FontRange::Latin1Supplement = {0xa0, 0xff};
inline FontRange FontRange::GeometricShapes = {0x25a0, 0x25ff};
inline FontRange FontRange::LatinExtendedA = {0x100, 0x17f};
inline FontRange FontRange::MiscellaneousSymbols = {0x2600, 0x26ff};
inline FontRange FontRange::LatinExtendedB = {0x180, 0x24f};
inline FontRange FontRange::Dingbats = {0x2700, 0x27bf};
inline FontRange FontRange::IpaExtensions = {0x250, 0x2af};
inline FontRange FontRange::MiscellaneousMathematicalSymbolsA = {0x27c0, 0x27ef};
inline FontRange FontRange::SpacingModifierLetters = {0x2b0, 0x2ff};
inline FontRange FontRange::SupplementalArrowsA = {0x27f0, 0x27ff};
inline FontRange FontRange::CombiningDiacriticalMarks = {0x300, 0x36f};
inline FontRange FontRange::BraillePatterns = {0x2800, 0x28ff};
inline FontRange FontRange::GreekAndCoptic = {0x370, 0x3ff};
inline FontRange FontRange::SupplementalArrowsB = {0x2900, 0x297f};
inline FontRange FontRange::Cyrillic = {0x400, 0x4ff};
inline FontRange FontRange::MiscellaneousMathematicalSymbolsB = {0x2980, 0x29ff};
inline FontRange FontRange::CyrillicSupplementary = {0x500, 0x52f};
inline FontRange FontRange::SupplementalMathematicalOperators = {0x2a00, 0x2aff};
inline FontRange FontRange::Armenian = {0x530, 0x58f};
inline FontRange FontRange::MiscellaneousSymbolsAndArrows = {0x2b00, 0x2bff};
inline FontRange FontRange::Hebrew = {0x590, 0x5ff};
inline FontRange FontRange::CjkRadicalsSupplement = {0x2e80, 0x2eff};
inline FontRange FontRange::Arabic = {0x600, 0x6ff};
inline FontRange FontRange::KangxiRadicals = {0x2f00, 0x2fdf};
inline FontRange FontRange::Syriac = {0x700, 0x74f};
inline FontRange FontRange::IdeographicDescriptionCharacters = {0x2ff0, 0x2fff};
inline FontRange FontRange::Thaana = {0x780, 0x7bf};
inline FontRange FontRange::CjkSymbolsAndPunctuation = {0x3000, 0x303f};
inline FontRange FontRange::Devanagari = {0x900, 0x97f};
inline FontRange FontRange::Hiragana = {0x3040, 0x309f};
inline FontRange FontRange::Bengali = {0x980, 0x9ff};
inline FontRange FontRange::Katakana = {0x30a0, 0x30ff};
inline FontRange FontRange::Gurmukhi = {0xa00, 0xa7f};
inline FontRange FontRange::Bopomofo = {0x3100, 0x312f};
inline FontRange FontRange::Gujarati = {0xa80, 0xaff};
inline FontRange FontRange::HangulCompatibilityJamo = {0x3130, 0x318f};
inline FontRange FontRange::Oriya = {0xb00, 0xb7f};
inline FontRange FontRange::Kanbun = {0x3190, 0x319f};
inline FontRange FontRange::Tamil = {0xb80, 0xbff};
inline FontRange FontRange::BopomofoExtended = {0x31a0, 0x31bf};
inline FontRange FontRange::Telugu = {0xc00, 0xc7f};
inline FontRange FontRange::KatakanaPhoneticExtensions = {0x31f0, 0x31ff};
inline FontRange FontRange::Kannada = {0xc80, 0xcff};
inline FontRange FontRange::EnclosedCjkLettersAndMonths = {0x3200, 0x32ff};
inline FontRange FontRange::Malayalam = {0xd00, 0xd7f};
inline FontRange FontRange::CjkCompatibility = {0x3300, 0x33ff};
inline FontRange FontRange::Sinhala = {0xd80, 0xdff};
inline FontRange FontRange::CjkUnifiedIdeographsExtensionA = {0x3400, 0x4dbf};
inline FontRange FontRange::Thai = {0xe00, 0xe7f};
inline FontRange FontRange::YijingHexagramSymbols = {0x4dc0, 0x4dff};
inline FontRange FontRange::Lao = {0xe80, 0xeff};
inline FontRange FontRange::CjkUnifiedIdeographs = {0x4e00, 0x9fff};
inline FontRange FontRange::Tibetan = {0xf00, 0xfff};
inline FontRange FontRange::YiSyllables = {0xa000, 0xa48f};
inline FontRange FontRange::Myanmar = {0x1000, 0x109f};
inline FontRange FontRange::YiRadicals = {0xa490, 0xa4cf};
inline FontRange FontRange::Georgian = {0x10a0, 0x10ff};
inline FontRange FontRange::HangulSyllables = {0xac00, 0xd7af};
inline FontRange FontRange::HangulJamo = {0x1100, 0x11ff};
inline FontRange FontRange::HighSurrogates = {0xd800, 0xdb7f};
inline FontRange FontRange::Ethiopic = {0x1200, 0x137f};
inline FontRange FontRange::HighPrivateUseSurrogates = {0xdb80, 0xdbff};
inline FontRange FontRange::Cherokee = {0x13a0, 0x13ff};
inline FontRange FontRange::LowSurrogates = {0xdc00, 0xdfff};
inline FontRange FontRange::UnifiedCanadianAboriginalSyllabics = {0x1400, 0x167f};
inline FontRange FontRange::PrivateUseArea = {0xe000, 0xf8ff};
inline FontRange FontRange::Ogham = {0x1680, 0x169f};
inline FontRange FontRange::CjkCompatibilityIdeographs = {0xf900, 0xfaff};
inline FontRange FontRange::Runic = {0x16a0, 0x16ff};
inline FontRange FontRange::AlphabeticPresentationForms = {0xfb00, 0xfb4f};
inline FontRange FontRange::Tagalog = {0x1700, 0x171f};
inline FontRange FontRange::ArabicPresentationFormsA = {0xfb50, 0xfdff};
inline FontRange FontRange::Hanunoo = {0x1720, 0x173f};
inline FontRange FontRange::VariationSelectors = {0xfe00, 0xfe0f};
inline FontRange FontRange::Buhid = {0x1740, 0x175f};
inline FontRange FontRange::CombiningHalfMarks = {0xfe20, 0xfe2f};
inline FontRange FontRange::Tagbanwa = {0x1760, 0x177f};
inline FontRange FontRange::CjkCompatibilityForms = {0xfe30, 0xfe4f};
inline FontRange FontRange::Khmer = {0x1780, 0x17ff};
inline FontRange FontRange::SmallFormVariants = {0xfe50, 0xfe6f};
inline FontRange FontRange::Mongolian = {0x1800, 0x18af};
inline FontRange FontRange::ArabicPresentationFormsB = {0xfe70, 0xfeff};
inline FontRange FontRange::Limbu = {0x1900, 0x194f};
inline FontRange FontRange::HalfwidthAndFullwidthForms = {0xff00, 0xffef};
inline FontRange FontRange::TaiLe = {0x1950, 0x197f};
inline FontRange FontRange::Specials = {0xfff0, 0xffff};
inline FontRange FontRange::KhmerSymbols = {0x19e0, 0x19ff};
inline FontRange FontRange::LinearBSyllabary = {0x10000, 0x1007f};
inline FontRange FontRange::PhoneticExtensions = {0x1d00, 0x1d7f};
inline FontRange FontRange::LinearBIdeograms = {0x10080, 0x100ff};
inline FontRange FontRange::LatinExtendedAdditional = {0x1e00, 0x1eff};
inline FontRange FontRange::AegeanNumbers = {0x10100, 0x1013f};
inline FontRange FontRange::GreekExtended = {0x1f00, 0x1fff};
inline FontRange FontRange::OldItalic = {0x10300, 0x1032f};
inline FontRange FontRange::GeneralPunctuation = {0x2000, 0x206f};
inline FontRange FontRange::Gothic = {0x10330, 0x1034f};
inline FontRange FontRange::SuperscriptsAndSubscripts = {0x2070, 0x209f};
inline FontRange FontRange::Ugaritic = {0x10380, 0x1039f};
inline FontRange FontRange::CurrencySymbols = {0x20a0, 0x20cf};
inline FontRange FontRange::Deseret = {0x10400, 0x1044f};
inline FontRange FontRange::CombiningDiacriticalMarksForSymbols = {0x20d0, 0x20ff};
inline FontRange FontRange::Shavian = {0x10450, 0x1047f};
inline FontRange FontRange::LetterlikeSymbols = {0x2100, 0x214f};
inline FontRange FontRange::Osmanya = {0x10480, 0x104af};
inline FontRange FontRange::NumberForms = {0x2150, 0x218f};
inline FontRange FontRange::CypriotSyllabary = {0x10800, 0x1083f};
inline FontRange FontRange::Arrows = {0x2190, 0x21ff};
inline FontRange FontRange::ByzantineMusicalSymbols = {0x1d000, 0x1d0ff};
inline FontRange FontRange::MathematicalOperators = {0x2200, 0x22ff};
inline FontRange FontRange::MusicalSymbols = {0x1d100, 0x1d1ff};
inline FontRange FontRange::MiscellaneousTechnical = {0x2300, 0x23ff};
inline FontRange FontRange::TaiXuanJingSymbols = {0x1d300, 0x1d35f};
inline FontRange FontRange::ControlPictures = {0x2400, 0x243f};
inline FontRange FontRange::MathematicalAlphanumericSymbols = {0x1d400, 0x1d7ff};
inline FontRange FontRange::OpticalCharacterRecognition = {0x2440, 0x245f};
inline FontRange FontRange::CjkUnifiedIdeographsExtensionB = {0x20000, 0x2a6df};
inline FontRange FontRange::EnclosedAlphanumerics = {0x2460, 0x24ff};
inline FontRange FontRange::CjkCompatibilityIdeographsSupplement = {0x2f800, 0x2fa1f};
inline FontRange FontRange::BoxDrawing = {0x2500, 0x257f};
inline FontRange FontRange::Tags = {0xe0000, 0xe007f};

struct Glyph {
    Recti textureRect;
    float xOffset; // на сколько смещается буква вправо относительно позиции курсора
    float yOffset; // на сколько смещается буква вниз относительно позиции курсора
    float xAdvance; // на сколько смещать курсор вправо после отрисовки буквы
};

struct Font {
    float lineHeight;
    float base;
    std::shared_ptr<Texture> fontAtlas;
    std::unordered_map<unsigned int, Glyph> glyphs;
};

class FontManager {
  public:
    static FontManager* instance();

    void loadFont(const std::filesystem::path& path, const std::string& id, float lineHeight);
    void loadBitmapFont(const std::string& path, const std::string& id);

    const Font& getFont(const std::string& id) const;

  private:
    std::unordered_map<std::string, Font> m_fonts;
};

NS_SPECTRUM_END