module tokens;


// Token

auto Token::Create(TokenType type) -> uptr_t<Token> {
    return uptr_t<Token>{
        new Token{ type }
    };
}

auto Token::Destroy(Token* token) -> void {
    switch (token->type) {
        case TokenType::eIdentifier:
            SelfDestructor<IdentifierToken>{}(static_cast<IdentifierToken*>(token)); break;
        case TokenType::eNumber:
            SelfDestructor<NumberToken>{}(static_cast<NumberToken*>(token)); break;
        default:
            delete token; break;
    }
}

// IdentifierToken

auto IdentifierToken::Create(std::string name) -> uptr_t<IdentifierToken> {
    return uptr_t<IdentifierToken> {
        new IdentifierToken{ { TokenType::eIdentifier }, std::move(name) }
    };
}

// NumberToken

auto NumberToken::Create(f64 value) -> uptr_t<NumberToken> {
    return uptr_t<NumberToken>{
        new NumberToken{ { TokenType::eNumber }, value }
    };
}

