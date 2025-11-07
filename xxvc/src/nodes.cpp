module;

#include <cassert>

module nodes;


// BinaryOperatorNode

auto BinaryOperatorNode::Create(BinaryOperatorType type) -> uptr_t<BinaryOperatorNode> {
    return uptr_t<BinaryOperatorNode>{
        new BinaryOperatorNode{ {}, type }
    };
}

// ExpressionNode

auto ExpressionNode::Destroy(ExpressionNode* node) -> void {
    switch (node->type) {
    case ExpressionType::eBinaryExpression:
        SelfDestructor<BinaryExpressionNode>{}(static_cast<BinaryExpressionNode*>(node)); break;
    case ExpressionType::eFunctionCallExpression:
        SelfDestructor<FunctionCallExpressionNode>{}(static_cast<FunctionCallExpressionNode*>(node)); break;
    case ExpressionType::eVariableExpression:
        SelfDestructor<VariableExpressionNode>{}(static_cast<VariableExpressionNode*>(node)); break;
    case ExpressionType::eNumberExpression:
        SelfDestructor<NumberExpressionNode>{}(static_cast<NumberExpressionNode*>(node)); break;
    case ExpressionType::eEmptyExpression:
        SelfDestructor<EmptyExpressionNode>{}(static_cast<EmptyExpressionNode*>(node)); break;
    default:
        assert(false && "add case");
    }
}

// BinaryExpressionNode

auto BinaryExpressionNode::Create(uptr_t<BinaryOperatorNode> binaryOperator, uptr_t<ExpressionNode> lhs, uptr_t<ExpressionNode> rhs) -> uptr_t<BinaryExpressionNode> {
    return uptr_t<BinaryExpressionNode>{
        new BinaryExpressionNode{ { {}, ExpressionType::eBinaryExpression }, std::move(binaryOperator), std::move(lhs), std::move(rhs) }
    };
}

// FunctionCallExpressionNode

auto FunctionCallExpressionNode::Create(std::string name, std::vector<uptr_t<ExpressionNode>> args) -> uptr_t<FunctionCallExpressionNode> {
    return uptr_t<FunctionCallExpressionNode>{
        new FunctionCallExpressionNode{ { {}, ExpressionType::eFunctionCallExpression }, std::move(name), std::move(args) }
    };
}

// VariableExpressionNode

auto VariableExpressionNode::Create(std::string name) -> uptr_t<VariableExpressionNode> {
    return uptr_t<VariableExpressionNode>{
        new VariableExpressionNode{ { {}, ExpressionType::eVariableExpression }, std::move(name) }
    };
}

// NumberExpressionNode

auto NumberExpressionNode::Create(f64 value) -> uptr_t<NumberExpressionNode> {
    return uptr_t<NumberExpressionNode>{
        new NumberExpressionNode{ { {}, ExpressionType::eNumberExpression }, value }
    };
}

// EmptyExpressionNode

auto EmptyExpressionNode::Create() -> uptr_t<EmptyExpressionNode> {
    return uptr_t<EmptyExpressionNode>{
        new EmptyExpressionNode{ { {}, ExpressionType::eEmptyExpression } }
    };
}

// FunctionStatementNode

auto FunctionStatementNode::Destroy(FunctionStatementNode* node) -> void {
    switch (node->type) {
    case FunctionStatementType::eVariableDeclaration:
        SelfDestructor<VariableDeclarationNode>{}(static_cast<VariableDeclarationNode*>(node)); break;
    case FunctionStatementType::eVariableDefinition:
        SelfDestructor<VariableDefinitionNode>{}(static_cast<VariableDefinitionNode*>(node)); break;
    case FunctionStatementType::eReturnStatement:
        SelfDestructor<ReturnStatementNode>{}(static_cast<ReturnStatementNode*>(node)); break;
    default:
        assert(false && "add case");
    }
}

// VariableDeclarationNode

auto VariableDeclarationNode::Create(std::string name) -> uptr_t<VariableDeclarationNode> {
    return uptr_t<VariableDeclarationNode>{
        new VariableDeclarationNode{ { {}, FunctionStatementType::eVariableDeclaration }, std::move(name) }
    };
}

// VariableDefinitionNode

auto VariableDefinitionNode::Create(std::string name, uptr_t<ExpressionNode> expression) -> uptr_t<VariableDefinitionNode> {
    return uptr_t<VariableDefinitionNode>{
        new VariableDefinitionNode{ { {}, FunctionStatementType::eVariableDefinition }, std::move(name), std::move(expression) }
    };
}

// ReturnStatementNode

auto ReturnStatementNode::Create(uptr_t<ExpressionNode> expression) -> uptr_t<ReturnStatementNode> {
    return uptr_t<ReturnStatementNode>{
        new ReturnStatementNode{ { {}, FunctionStatementType::eReturnStatement }, std::move(expression) }
    };
}

// FunctionPrototypeNode

auto FunctionPrototypeNode::Create(std::string name, std::vector<std::string> args) -> uptr_t<FunctionPrototypeNode> {
    return uptr_t<FunctionPrototypeNode>{
        new FunctionPrototypeNode{ {}, std::move(name), std::move(args) }
    };
}

// ModuleStatementNode

auto ModuleStatementNode::Destroy(ModuleStatementNode* node) -> void {
    switch (node->type) {
    case ModuleStatementType::eFunctionDeclaration:
        SelfDestructor<FunctionDeclarationNode>{}(static_cast<FunctionDeclarationNode*>(node)); break;
    case ModuleStatementType::eFunctionDefinition:
        SelfDestructor<FunctionDefinitionNode>{}(static_cast<FunctionDefinitionNode*>(node)); break;
    case ModuleStatementType::eExternFunctionDeclaration:
        SelfDestructor<ExternFunctionDeclarationNode>{}(static_cast<ExternFunctionDeclarationNode*>(node)); break;
    default:
        assert(false && "add case");
    }
}

// FunctionDeclarationNode

auto FunctionDeclarationNode::Create(uptr_t<FunctionPrototypeNode> prototype) -> uptr_t<FunctionDeclarationNode> {
    return uptr_t<FunctionDeclarationNode>{
        new FunctionDeclarationNode{ { {}, ModuleStatementType::eFunctionDeclaration }, std::move(prototype) }
    };
}

// FunctionDefinitionNode

auto FunctionDefinitionNode::Create(uptr_t<FunctionPrototypeNode> prototype, std::vector<uptr_t<FunctionStatementNode>> body) -> uptr_t<FunctionDefinitionNode> {
    return uptr_t<FunctionDefinitionNode>{
        new FunctionDefinitionNode{ { {}, ModuleStatementType::eFunctionDefinition }, std::move(prototype), std::move(body) }
    };
}

// ExternFunctionDeclarationNode

auto ExternFunctionDeclarationNode::Create(uptr_t<FunctionPrototypeNode> prototype) -> uptr_t<ExternFunctionDeclarationNode> {
    return uptr_t<ExternFunctionDeclarationNode>{
        new ExternFunctionDeclarationNode{ { {}, ModuleStatementType::eExternFunctionDeclaration }, std::move(prototype) }
    };
}

// ModuleNode

auto ModuleNode::Create(std::vector<uptr_t<ModuleStatementNode>> body) -> uptr_t<ModuleNode> {
    return uptr_t<ModuleNode>{
        new ModuleNode{ {}, std::move(body) }
    };
}
