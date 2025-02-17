#ifndef LANGUAGE_H
#define LANGUAGE_H
enum supportedLanguage{
    EN,RU,UA
};
inline const char* ToString(supportedLanguage v)
{
    switch (v)
    {
        case EN:   return "En";
        case RU:   return "Ru";
        case UA:    return "Ua";
        default:      return "[UnsupportedLanguage]";
    }
}
#endif // LANGUAGE_H
