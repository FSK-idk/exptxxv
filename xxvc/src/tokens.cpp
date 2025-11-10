module tokens;


// Token

auto Token::Create(TokenType type) -> uptr_t<Token> {
    return make_uptr(Token{ type });
}

auto Token::Destroy(Token* token) -> void {
    switch (token->type) {
        case TokenType::eIdentifier:
            return SelfDestructor<IdentifierToken>{}(static_cast<IdentifierToken*>(token));
        case TokenType::eInteger:
            return SelfDestructor<IntegerToken>{}(static_cast<IntegerToken*>(token));
        case TokenType::eUnsigned:
            return SelfDestructor<UnsignedToken>{}(static_cast<UnsignedToken*>(token));
        case TokenType::eFloating:
            return SelfDestructor<FloatingToken>{}(static_cast<FloatingToken*>(token));
        // TODO: introduce TokenType::eSpecial and TokenType::eKeyword and add here assert as default
        default:
            delete token; break;
    }
}

// IdentifierToken

auto IdentifierToken::Create(std::string name) -> uptr_t<IdentifierToken> {
    return make_uptr(IdentifierToken{ { TokenType::eIdentifier }, std::move(name) });
}

// IntegerToken

auto IntegerToken::Create(std::string value, BitSize size) -> uptr_t<IntegerToken> {
    return make_uptr(IntegerToken{ { TokenType::eInteger }, std::move(value), size });
}

// UnsignedToken

auto UnsignedToken::Create(std::string value, BitSize size) -> uptr_t<UnsignedToken> {
    return make_uptr(UnsignedToken{ { TokenType::eUnsigned }, std::move(value), size });
}

// FloatingToken

auto FloatingToken::Create(std::string value, BitSize size) -> uptr_t<FloatingToken> {
    return make_uptr(FloatingToken{ { TokenType::eFloating }, std::move(value), size });
}
