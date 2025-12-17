#pragma once

#include "../../Core/include/ICommand.h"

class CreateRoomCommand : public ICommand {
public:
	void Execute() override;
};