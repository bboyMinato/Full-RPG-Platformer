#include "..\include\Text.h"
#include "..\include\Engine.h"

TTF_Font* Text::LoadFont(std::string id, std::string filepath, int fontSize)
{
    _font = TTF_OpenFont(filepath.c_str(), fontSize);

    if (_font == nullptr)
        std::cout << "Failed to load the font! Error: " << TTF_GetError() << std::endl;

    _fontMap[id] = _font; 

    return _font;
}

TTF_Font* Text::GetFont(std::string id)
{
    return _fontMap[id];
}

SDL_Texture* Text::CreateText(std::string id, std::string text, TTF_Font* font, SDL_Color color)
{    
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface)
        std::cerr << "Failed to create a surface!" << std::endl;

    _textTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), textSurface);
    if (!_textTexture)
        std::cerr << "Failed to create a texture!" << std::endl;
    
    SDL_FreeSurface(textSurface);

    SDL_QueryTexture(_textTexture, nullptr, nullptr, &_dst.w, &_dst.h);

    _fontTextureMap[id] = _textTexture;

    return _textTexture;
}

void Text::Render(std::string id, int x, int y)
{
    _dst.x = x;
    _dst.y = y;

    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), _fontTextureMap[id], nullptr, &_dst);
}

void Text::Clean()
{
    for (auto it = _fontMap.begin(); it != _fontMap.end(); it++)
        TTF_CloseFont(it->second);

    _fontMap.clear();
}
