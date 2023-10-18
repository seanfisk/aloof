#include <stdio.h>
#include <unistd.h>
#include <IOKit/pwr_mgt/IOPMLib.h>

int main(int argc, char *argv[]) {
  puts("Hello, world!");

  IOPMAssertionID assertionID;
  const IOReturn result = IOPMAssertionCreateWithDescription(
      /*AssertionType=*/kIOPMAssertionTypePreventUserIdleSystemSleep,
      /*Name=*/CFSTR("unattend command-line tool"),
      /*Details=*/CFSTR("test assertion"),
      /*HumanReadableReason=*/
      CFSTR("Run time-consuming operation in background"),
      /*LocalizationBundlePath=*/NULL,
      /*Timeout=*/0,

      // I think this differs from kIOPMAssertionTimeoutActionTurnOff in that
      // the assertion is deleted, not just made inactive
      /*TimeoutAction=*/kIOPMAssertionTimeoutActionRelease, &assertionID);

  sleep(30 /*seconds*/);

  if (result != kIOReturnSuccess) {
    fputs("Failed to create power assertion", stderr);
  }

  return 0;
}
