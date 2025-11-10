module;

#include <cassert>

module nodes;


// Nodes

// ModuleNode

auto ModuleNode::Create(std::vector<uptr_t<ModuleStatementNode>> stmts) -> uptr_t<ModuleNode> {
    return make_uptr(ModuleNode{ {}, std::move(stmts) });
}

// ModuleStatementNode

auto ModuleStatementNode::Destroy(ModuleStatementNode* node) -> void {
    switch (node->type) {
    case ModuleStatementType::eFunctionDeclaration:
        return SelfDestructor<FunctionDeclarationNode>{}(static_cast<FunctionDeclarationNode*>(node));
    case ModuleStatementType::eFunctionDefinition:
        return SelfDestructor<FunctionDefinitionNode>{}(static_cast<FunctionDefinitionNode*>(node));
    case ModuleStatementType::eExternFunctionDeclaration:
        return SelfDestructor<ExternFunctionDeclarationNode>{}(static_cast<ExternFunctionDeclarationNode*>(node));
    default:
        assert(false && "add case");
    }
}

// FunctionDeclarationNode

auto FunctionDeclarationNode::Create(uptr_t<FunctionPrototypeSeminode> proto) -> uptr_t<FunctionDeclarationNode> {
    return make_uptr(FunctionDeclarationNode{ { {}, ModuleStatementType::eFunctionDeclaration }, std::move(proto->name), std::move(proto->vars), proto->retType });
}

// FunctionDefinitionNode

auto FunctionDefinitionNode::Create(uptr_t<FunctionPrototypeSeminode> proto, uptr_t<FunctionStatementBlockSeminode> block) -> uptr_t<FunctionDefinitionNode> {
    return make_uptr(FunctionDefinitionNode{ { {}, ModuleStatementType::eFunctionDefinition }, std::move(proto->name), std::move(proto->vars), proto->retType, std::move(block->stmts) });
}

// ExternFunctionDeclarationNode

auto ExternFunctionDeclarationNode::Create(uptr_t<FunctionPrototypeSeminode> proto) -> uptr_t<ExternFunctionDeclarationNode> {
    return make_uptr(ExternFunctionDeclarationNode{ { {}, ModuleStatementType::eExternFunctionDeclaration }, std::move(proto->name), std::move(proto->vars), proto->retType });
}

// FunctionStatementNode

auto FunctionStatementNode::Destroy(FunctionStatementNode* node) -> void {
    switch (node->type) {
    case FunctionStatementType::eVariableDeclaration:
        return SelfDestructor<VariableDeclarationNode>{}(static_cast<VariableDeclarationNode*>(node));
    case FunctionStatementType::eVariableDefinition:
        return SelfDestructor<VariableDefinitionNode>{}(static_cast<VariableDefinitionNode*>(node));
    case FunctionStatementType::eReturnStatement:
        return SelfDestructor<ReturnStatementNode>{}(static_cast<ReturnStatementNode*>(node));
    default:
        assert(false && "add case");
    }
}

// VariableDeclarationNode

auto VariableDeclarationNode::Create(uptr_t<VariablePrototypeSeminode> proto) -> uptr_t<VariableDeclarationNode> {
    return make_uptr(VariableDeclarationNode{ { {}, FunctionStatementType::eVariableDeclaration }, std::move(proto->name), proto->type });
}

// VariableDefinitionNode

auto VariableDefinitionNode::Create(uptr_t<VariablePrototypeSeminode> proto, uptr_t<ExpressionBlockSeminode> block) -> uptr_t<VariableDefinitionNode> {
    return make_uptr(VariableDefinitionNode{ { {}, FunctionStatementType::eVariableDefinition }, std::move(proto->name), proto->type, std::move(block->expr) });
}

// ReturnStatementNode

auto ReturnStatementNode::Create(PrimaryTypeType retType, uptr_t<ExpressionNode> expr) -> uptr_t<ReturnStatementNode> {
    return make_uptr(ReturnStatementNode{ { {}, FunctionStatementType::eReturnStatement }, retType, std::move(expr) });
}

// ExpressionNode

auto ExpressionNode::Create(uptr_t<NonEmptyExpressionSeminode> expr) -> uptr_t<ExpressionNode> {
    return uptr_cast<ExpressionNode>(std::move(expr->expr));
}

auto ExpressionNode::Create(uptr_t<PrimaryExpressionSeminode> expr) -> uptr_t<ExpressionNode> {
    return uptr_cast<ExpressionNode>(std::move(expr->expr));
}

auto ExpressionNode::Destroy(ExpressionNode* node) -> void {
    switch (node->type) {
    case ExpressionType::eBinaryExpression:
        return SelfDestructor<BinaryExpressionNode>{}(static_cast<BinaryExpressionNode*>(node));
    case ExpressionType::eFunctionCallExpression:
        return SelfDestructor<FunctionCallExpressionNode>{}(static_cast<FunctionCallExpressionNode*>(node));
    case ExpressionType::eVariableExpression:
        return SelfDestructor<VariableExpressionNode>{}(static_cast<VariableExpressionNode*>(node));
    case ExpressionType::eIntegerExpression:
        return SelfDestructor<IntegerExpressionNode>{}(static_cast<IntegerExpressionNode*>(node));
    case ExpressionType::eUnsignedExpression:
        return SelfDestructor<UnsignedExpressionNode>{}(static_cast<UnsignedExpressionNode*>(node));
    case ExpressionType::eFloatingExpression:
        return SelfDestructor<FloatingExpressionNode>{}(static_cast<FloatingExpressionNode*>(node));
    case ExpressionType::eEmptyExpression:
        return SelfDestructor<EmptyExpressionNode>{}(static_cast<EmptyExpressionNode*>(node));
    default:
        assert(false && "add case");
    }
}

// BinaryExpressionNode

auto BinaryExpressionNode::Create(PrimaryTypeType retType, uptr_t<BinaryOperatorSeminode> op, uptr_t<NonEmptyExpressionSeminode> lhs, uptr_t<NonEmptyExpressionSeminode> rhs) -> uptr_t<BinaryExpressionNode> {
    return make_uptr(BinaryExpressionNode{ { {}, ExpressionType::eBinaryExpression, retType }, op->type, std::move(lhs->expr), std::move(rhs->expr) });
}

// FunctionCallExpressionNode

auto FunctionCallExpressionNode::Create(PrimaryTypeType retType, std::string name, uptr_t<NonEmptyExpressionListSeminode> list) -> uptr_t<FunctionCallExpressionNode> {
    return make_uptr(FunctionCallExpressionNode{ { {}, ExpressionType::eFunctionCallExpression, retType }, std::move(name), std::move(list->exprs) });
}

// VariableExpressionNode

auto VariableExpressionNode::Create(PrimaryTypeType retType, std::string name) -> uptr_t<VariableExpressionNode> {
    return make_uptr(VariableExpressionNode{ { {}, ExpressionType::eVariableExpression, retType }, std::move(name) });
}

// IntegerExpressionNode

auto getIntegerType(BitSize size) -> PrimaryTypeType {
    switch (size) {
    case BitSize::e64: return PrimaryTypeType::eI64;
    case BitSize::e32: return PrimaryTypeType::eI32;
    case BitSize::e16: return PrimaryTypeType::eI16;
    default:
        assert(false && "add case");
    }
}

auto IntegerExpressionNode::Create(std::string value, BitSize size) -> uptr_t<IntegerExpressionNode> {
    return make_uptr(IntegerExpressionNode{ { {}, ExpressionType::eIntegerExpression, getIntegerType(size) }, std::move(value), size });
}

// UnsignedExpressionNode

auto getUnsignedType(BitSize size) -> PrimaryTypeType {
    switch (size) {
    case BitSize::e64: return PrimaryTypeType::eU64;
    case BitSize::e32: return PrimaryTypeType::eU32;
    case BitSize::e16: return PrimaryTypeType::eU16;
    default:
        assert(false && "add case");
    }
}

auto UnsignedExpressionNode::Create(std::string value, BitSize size) -> uptr_t<UnsignedExpressionNode> {
    return make_uptr(UnsignedExpressionNode{ { {}, ExpressionType::eUnsignedExpression, getUnsignedType(size) }, std::move(value), size });
}

// FloatingExpressionNode

auto getFloatingType(BitSize size) -> PrimaryTypeType {
    switch (size) {
    case BitSize::e64: return PrimaryTypeType::eF64;
    case BitSize::e32: return PrimaryTypeType::eF32;
    default:
        assert(false && "floating can only has 32 and 64 bits");
    }
}

auto FloatingExpressionNode::Create(std::string value, BitSize size) -> uptr_t<FloatingExpressionNode> {
    return make_uptr(FloatingExpressionNode{ { {}, ExpressionType::eFloatingExpression, getFloatingType(size) }, std::move(value), size });
}

// EmptyExpressionNode

auto EmptyExpressionNode::Create() -> uptr_t<EmptyExpressionNode> {
    return make_uptr(EmptyExpressionNode{ { {}, ExpressionType::eEmptyExpression, PrimaryTypeType::eVoid } });
}

// Seminodes

// FunctionStatementBlockSeminode

auto FunctionStatementBlockSeminode::Create(std::vector<uptr_t<FunctionStatementNode>> stmts) -> uptr_t<FunctionStatementBlockSeminode> {
    return make_uptr(FunctionStatementBlockSeminode{ {}, std::move(stmts) });
}

// ExpressionBlockSeminode

auto ExpressionBlockSeminode::Create(uptr_t<ExpressionNode> expr) -> uptr_t<ExpressionBlockSeminode> {
    return make_uptr(ExpressionBlockSeminode{ {}, std::move(expr) });
}

// NonEmptyExpressionListSeminode

auto NonEmptyExpressionListSeminode::Create(std::vector<uptr_t<NonEmptyExpressionSeminode>> exprs) -> uptr_t<NonEmptyExpressionListSeminode> {
    std::vector<uptr_t<ExpressionNode>> exprs_; exprs_.reserve(exprs.size());
    for (auto& expr : exprs) exprs_.emplace_back(std::move(expr->expr));
    return make_uptr(NonEmptyExpressionListSeminode{ {}, std::move(exprs_) });
}

// NonEmptyExpressionSeminode

auto NonEmptyExpressionSeminode::Create(uptr_t<ExpressionNode> expr) -> uptr_t<NonEmptyExpressionSeminode> {
    return make_uptr(NonEmptyExpressionSeminode{ {}, std::move(expr) });
}

// PrimaryExpressionSeminode

auto PrimaryExpressionSeminode::Create(uptr_t<FunctionCallExpressionNode> expr) -> uptr_t<PrimaryExpressionSeminode> {
    return make_uptr(PrimaryExpressionSeminode{ {}, std::move(expr) });
}

auto PrimaryExpressionSeminode::Create(uptr_t<VariableExpressionNode> expr) -> uptr_t<PrimaryExpressionSeminode> {
    return make_uptr(PrimaryExpressionSeminode{ {}, std::move(expr) });
}

auto PrimaryExpressionSeminode::Create(uptr_t<EmptyExpressionNode> expr) -> uptr_t<PrimaryExpressionSeminode> {
    return make_uptr(PrimaryExpressionSeminode{ {}, std::move(expr) });
}

auto PrimaryExpressionSeminode::Create(uptr_t<IntegerExpressionNode> expr) -> uptr_t<PrimaryExpressionSeminode> {
    return make_uptr(PrimaryExpressionSeminode{ {}, std::move(expr) });
}

auto PrimaryExpressionSeminode::Create(uptr_t<UnsignedExpressionNode> expr) -> uptr_t<PrimaryExpressionSeminode> {
    return make_uptr(PrimaryExpressionSeminode{ {}, std::move(expr) });
}

auto PrimaryExpressionSeminode::Create(uptr_t<FloatingExpressionNode> expr) -> uptr_t<PrimaryExpressionSeminode> {
    return make_uptr(PrimaryExpressionSeminode{ {}, std::move(expr) });
}

auto PrimaryExpressionSeminode::Create(uptr_t<NonEmptyExpressionSeminode> expr) -> uptr_t<PrimaryExpressionSeminode> {
    return make_uptr(PrimaryExpressionSeminode{ {}, std::move(expr->expr) });
}

// BinaryOperatorSeminode

auto BinaryOperatorSeminode::Create(BinaryOperatorType type) -> uptr_t<BinaryOperatorSeminode> {
    return make_uptr(BinaryOperatorSeminode{ {}, type });
}

// FunctionPrototypeSeminode

auto FunctionPrototypeSeminode::Create(std::string name, uptr_t<FunctionTypeSeminode> type) -> uptr_t<FunctionPrototypeSeminode> {
    return make_uptr(FunctionPrototypeSeminode{ {}, std::move(name), std::move(type->vars), type->retType });
}

// FunctionTypeSeminode

auto FunctionTypeSeminode::Create(uptr_t<VariablePrototypeListSeminode> list, uptr_t<PrimaryTypeSeminode> type) -> uptr_t<FunctionTypeSeminode> {
    return make_uptr(FunctionTypeSeminode{ {}, std::move(list->vars), type->type });
}

// VariablePrototypeListSeminode

auto VariablePrototypeListSeminode::Create(std::vector<uptr_t<VariablePrototypeSeminode>> protos) -> uptr_t<VariablePrototypeListSeminode> {
    std::vector<std::pair<std::string, PrimaryTypeType>> vars_; vars_.reserve(protos.size());
    for (auto& [name, type] : protos | std::views::transform(&uptr_t<VariablePrototypeSeminode>::operator*)) vars_.emplace_back(std::move(name), type);
    return make_uptr(VariablePrototypeListSeminode{ {}, std::move(vars_) });
}

// VariablePrototypeSeminode

auto VariablePrototypeSeminode::Create(std::string name, uptr_t<PrimaryTypeSeminode> type) -> uptr_t<VariablePrototypeSeminode> {
    return make_uptr(VariablePrototypeSeminode{ {}, std::move(name), type->type });
}

// PrimaryTypeSeminode

auto PrimaryTypeSeminode::Create(PrimaryTypeType type) -> uptr_t<PrimaryTypeSeminode> {
    return make_uptr(PrimaryTypeSeminode{ {}, type });
}
