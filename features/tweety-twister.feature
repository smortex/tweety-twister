Feature: Tweety Twister
  Scenario: Checking a disk
    Given I copy the file "../../README.md" to "README.md"
    When I run `./check-canaries README.md`
    Then the exit status should be 1
    And the stderr should contain exactly:
    """
    check-canaries: Wrong canaries at beginning of device
    """
    When I run `./write-canaries README.md`
    Then the exit status should be 0
    When I run `./check-canaries README.md`
    Then the exit status should be 0
