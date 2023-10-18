#include <IOKit/pwr_mgt/IOPMLib.h>
#include <stdio.h>
#include <unistd.h>

void create_assertion() {
  puts("Creating assertion");

  IOPMAssertionID assertion_id;

  // See here for the difference between assertion types:
  // https://stackoverflow.com/a/66093676

  const CFStringRef assertion_type =
      kIOPMAssertionTypePreventUserIdleSystemSleep;
  // const CFStringRef assertion_type = kIOPMAssertionTypeNoIdleSleep;

  // Note: Limited to 128 characters
  const CFStringRef name = CFSTR("unattend command-line tool");

  // Both of these calls work, but IOPMAssertionCreateWithDescription is a bit
  // nicer as it provides a better message in `pmset -g assertions'.
  IOReturn result;
  if (true) {
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
        /*AssertionLevel=*/kIOPMAssertionLevelOn, name, &assertion_id);
  }

  if (result != kIOReturnSuccess) {
    fputs("Failed to create power assertion", stderr);
    exit(EXIT_FAILURE);
  }

  puts("Assertion created successfully");
}

int main(int argc, char *argv[]) {
  create_assertion();

  // puts("Sleeping");
  // sleep(10 /*seconds*/);

  puts("Replacing process");
  const char *prog = "/bin/bash";
  execl(prog, prog, "-c", "sleep 10");
  perror("unattend");
  return EXIT_FAILURE;

  // Assertion will be released automatically when the process exits. Look for ClientDied in `pmset -g assertionslog`.
}
