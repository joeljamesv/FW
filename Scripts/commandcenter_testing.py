from mimic_client import MimicClient

    def
    main()
    : client = MimicClient()

#Step 1 : send username and wait for password prompt
                   client.send_no_newline("root") recv =
          client
              .recv_until("password:") print("RECV after username ->",
                                             repr(recv))

#Step 2 : send password and wait for Entering Console
                  client.send_no_newline("password") recv = client.recv_until(
              "Entering Console") print("RECV after password ->", repr(recv))

#Send good command
                                                                good_cmd =
              "get:firefly:state:on" print(
                  "Sending good command:",
                  good_cmd) client.send_no_newline(good_cmd) recv =
                  client.recv_until("Command Accepted")
                      print("RECV for good command ->", repr(recv))

#Send bad command
                          bad_cmd =
                      "foo:bar:baz:qux" print(
                          "Sending bad command:",
                          bad_cmd) client.send_no_newline(bad_cmd) recv =
                          client
                              .recv_until("Invalid Command") print(
                                  "RECV for bad command ->", repr(recv))

#Send exit
                                  print("Sending exit") client.send_no_newline(
                                      "exit") recv =
                              client
                                  .recv_until("Console exited") print(
                                      "RECV after exit ->", repr(recv))

                                      client.close() print(
                                          "All steps OK — exiting with success")

                                          if __name__
                              == "__main__" : main()
