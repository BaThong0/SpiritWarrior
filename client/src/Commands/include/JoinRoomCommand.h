#pragma once

#include "../../Core/include/ICommand.h"

class JoinRoomCommand : public ICommand {
public:
	void Execute() override;
};