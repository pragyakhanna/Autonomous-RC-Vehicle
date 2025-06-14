#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/test_motor.h>

#include <uORB/topics/rc_channels.h>

// 0 = motor
// 1 = servo
#define DC_MOTOR 0
#define SERVO 1


extern "C" __EXPORT int p2p1_main(int argc, char *argv[]);

int p2p1_main(int argc, char *argv[]){
	//SERVO
	test_motor_s test_servo;
	// double servo_value = 0; // a number between 0 to 1

	//MOTOR
	test_motor_s test_motor;
	// double motor_value = 0; // a number between 0 to 1
	uORB::Publication<test_motor_s> test_motor_pub(ORB_ID(test_motor));

	// Remote Control
	int input_rc_handle;
	rc_channels_s rc_data;
	// double motor_value = 0;
	//Low - 1024
	//Mid - 1514
	//High - 2003

	PX4_INFO("The motor will be stopped and the angle will be centered");
	test_motor.timestamp = hrt_absolute_time();
	test_motor.motor_number = DC_MOTOR;
	test_motor.value = 0.548979;
	test_motor.action = test_motor_s::ACTION_RUN;
	test_motor.driver_instance = 0;
	test_motor.timeout_ms = 0;


	test_motor_pub.publish(test_motor);

	test_servo.timestamp = hrt_absolute_time();
	test_servo.motor_number = SERVO;
	test_servo.value = 0.5;
	test_servo.driver_instance = 0;
	test_servo.timeout_ms = 0;

	test_motor_pub.publish(test_servo);


	px4_sleep(3);


	// 0 - 0.5 - 1                RC: -1 - 0 - 1  --> +1  --> 0 - 1 - 2 --> /4 --> 0 - 0.25 - 0.5
	input_rc_handle = orb_subscribe(ORB_ID(rc_channels));
	orb_set_interval(input_rc_handle, 200);

	// LAST CAR USED 4
	while(1){
		orb_copy(ORB_ID(rc_channels), input_rc_handle, &rc_data);
		if((double)rc_data.channels[7] >0 ){
			break;
		}
		// Ch1 = LEFT RIGHT SERVO
		double angle = -1*(((double)rc_data.channels[0]) -0.534693);

		// Ch5 = REV and FWD
		double revFwd = (double)rc_data.channels[4] < 1.0 ? +1:-1;

		// Ch3 = MOTOR UP AND DOWN0
		double motorSpeed = 0.548979 + revFwd*(((double)rc_data.channels[2] + 1)/4);

		// PX4_INFO("LR %f, REVFWD %f, MOTOR %f",angle,revFwd,motorSpeed);
		PX4_INFO("MOTOR %f",motorSpeed);
		PX4_INFO("Motor angle is %f", angle);

		// Servo CONFIG
		test_servo.timestamp = hrt_absolute_time();
		test_servo.motor_number = SERVO;
		test_servo.value = (float)angle;
		test_servo.action = test_motor_s::ACTION_RUN;
		test_servo.driver_instance = 0;
		test_servo.timeout_ms = 0;

		// Motor CONFIG
		test_motor.timestamp = hrt_absolute_time();
		test_motor.motor_number = DC_MOTOR;
		test_motor.value = motorSpeed;
		test_motor.action = test_motor_s::ACTION_RUN;
		test_motor.driver_instance = 0;
		test_motor.timeout_ms = 0;

		test_motor_pub.publish(test_servo);
		test_motor_pub.publish(test_motor);
	}

	PX4_INFO("The motor will be stopped and the angle will be centered");
	test_motor.timestamp = hrt_absolute_time();
	test_motor.motor_number = DC_MOTOR;
	test_motor.value = 0.548979;
	test_motor.driver_instance = 0;
	test_motor.timeout_ms = 0;

	test_servo.timestamp = hrt_absolute_time();
	test_servo.motor_number = SERVO;
	test_servo.value = 0.5;
	test_servo.driver_instance = 0;
	test_servo.timeout_ms = 0;

	test_motor_pub.publish(test_servo);
	test_motor_pub.publish(test_motor);

	return 0;
 }
