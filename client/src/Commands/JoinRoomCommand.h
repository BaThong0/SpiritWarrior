#pragma once

#include "../Core/ICommand.h"

class JoinRoomCommand : public ICommand {
public:
	void Execute() override;
};