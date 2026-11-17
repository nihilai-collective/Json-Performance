
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1698.11 | 0.686483 | 1043.16ms | 18245 | 320 | 1.58331e+06 | 10246.6 | 0.131314 | 1.4534 | 1(Win) | true |
| Jsonifier | 1488.01 | 0.208808 | 1198.67ms | 18245 | 30 | 17885.1 | 11693.3 | 0.0570451 | 1.65913 | 2(Loss) | true |
| simdjson (ondemand) | 661.44 | 0.281084 | 2642.34ms | 18245 | 640 | 3.49912e+06 | 26305.9 | 0.00593937 | 3.73895 | 3(Loss) | true |
| Glaze | 551.999 | 0.093986 | 3214.13ms | 18245 | 4890 | 4.29186e+06 | 31521.4 | 0.346273 | 4.48099 | 4(Loss) | true |
