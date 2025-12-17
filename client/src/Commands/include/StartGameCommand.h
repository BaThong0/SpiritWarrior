#pragma once

#include "../../Core/include/ICommand.h"

class StartGameCommand : public ICommand {
public:
	void Execute() override;
};