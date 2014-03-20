#include "input/MotorInput.h"

namespace vlr
{
	MotorInput::MotorInput()
		: _enabled(false), _maxForce(0), _speed(0),
		_forwardButton(GLFW_KEY_UNKNOWN), _reverseButton(GLFW_KEY_UNKNOWN)
	{

	}

	void MotorInput::update(GLFWwindow* window, b2Joint* joint)
	{
		if (!_enabled)
			return;

		bool forwardKey = glfwGetKey(window, _forwardButton) != 0;
		bool reverseKey = glfwGetKey(window, _reverseButton) != 0;

		bool enableMotor = _enabled && (forwardKey != reverseKey);

		switch (joint->GetType())
		{
		case b2JointType::e_revoluteJoint:
			{
				b2RevoluteJoint* specJoint = (b2RevoluteJoint*)joint;

				specJoint->EnableMotor(enableMotor);

				if (enableMotor)
				{
					specJoint->SetMaxMotorTorque(_maxForce);
					specJoint->SetMotorSpeed(_speed * (reverseKey ? -1.0f : 1.0f));
				}
			}
			break;
		case b2JointType::e_wheelJoint:
			{
				b2WheelJoint* specJoint = (b2WheelJoint*)joint;

				specJoint->EnableMotor(enableMotor);

				if (enableMotor)
				{
					specJoint->SetMaxMotorTorque(_maxForce);
					specJoint->SetMotorSpeed(_speed * (reverseKey ? -1.0f : 1.0f));
				}
			}
			break;
		case b2JointType::e_prismaticJoint:
			{
				b2PrismaticJoint* specJoint = (b2PrismaticJoint*)joint;

				specJoint->EnableMotor(enableMotor);

				if (enableMotor)
				{
					specJoint->SetMaxMotorForce(_maxForce);
					specJoint->SetMotorSpeed(_speed * (reverseKey ? -1.0f : 1.0f));
				}
			}
			break;
		default:
			return;
		}
	}
}
