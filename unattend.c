#include <IOKit/pwr_mgt/IOPMLib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  puts("Hello, world!");

  IOPMAssertionID assertion_id;

  // See here for the difference between assertion types:
  // https://stackoverflow.com/a/66093676

  const CFStringRef assertion_type =
      kIOPMAssertionTypePreventUserIdleSystemSleep;

  // Note: Limited to 128 characters
  const CFStringRef name = CFSTR("unattend command-line tool");

  IOReturn result;
  /* result = IOPMAssertionCreateWithDescription( */
  /*     assertion_type, name, */
  /*     /\*Details=*\/CFSTR("test assertion"), */
  /*     /\*HumanReadableReason=*\/ */
  /*     CFSTR("Run time-consuming operation in background"), */
  /*     /\*LocalizationBundlePath=*\/NULL, */
  /*     /\*Timeout=*\/0, */

  /*     // I think this differs from kIOPMAssertionTimeoutActionTurnOff in that */
  /*     // the assertion is deleted, not just made inactive */
  /*     /\*TimeoutAction=*\/kIOPMAssertionTimeoutActionRelease, &assertion_id); */

  result = IOPMAssertionCreateWithName(
      assertion_type,
      /*AssertionLevel=*/kIOPMAssertionLevelOff, name & assertion_id);

  sleep(30 /*seconds*/);

  if (result != kIOReturnSuccess) {
    fputs("Failed to create power assertion", stderr);
  }

  return 0;
}
