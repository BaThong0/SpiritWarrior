#pragma once

#include "../Core/ICommand.h"

class StartGameCommand : public ICommand {
public:
	void Execute() override;
};