#include <IOKit/pwr_mgt/IOPMLib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  puts("Creating assertion");

  IOPMAssertionID assertion_id;

  // See here for the difference between assertion types:
  // https://stackoverflow.com/a/66093676

  const CFStringRef assertion_type =
      kIOPMAssertionTypePreventUserIdleSystemSleep;

  // Note: Limited to 128 characters
  const CFStringRef name = CFSTR("unattend command-line tool");

  IOReturn result;
  if (false) {
    result = IOPMAssertionCreateWithDescription(
        assertion_type, name,
        /*Details=*/CFSTR("test assertion"),
        /*HumanReadableReason=*/
        CFSTR("Run time-consuming operation in background"),
        /*LocalizationBundlePath=*/NULL,
        /*Timeout=*/0,

        // I think this differs from kIOPMAssertionTimeoutActionTurnOff in that
        // the assertion is deleted, not just made inactive
        /*TimeoutAction=*/kIOPMAssertionTimeoutActionRelease, &assertion_id);
  } else {
    result = IOPMAssertionCreateWithName(
        assertion_type,
        /*AssertionLevel=*/kIOPMAssertionLevelOff, name, &assertion_id);
  }

  if (result != kIOReturnSuccess) {
    fputs("Failed to create power assertion", stderr);
    return EXIT_FAILURE;
  }

  puts("Assertion created successfully");

  puts("Sleeping");

  sleep(30 /*seconds*/);

  puts("Exiting");

  return EXIT_SUCCESS;
}
