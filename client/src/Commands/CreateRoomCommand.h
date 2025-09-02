#pragma once

#include "../Core/ICommand.h"

class CreateRoomCommand : public ICommand {
public:
	void Execute() override;
};