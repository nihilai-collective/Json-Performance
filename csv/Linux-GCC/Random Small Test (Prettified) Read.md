
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2741.31 | 0.0670621 | 1002.39ms | 8051 | 2560 | 9031.88 | 2800.86 | 0.155383 | 1.90512 | 8.44454 | 1.52851 | 0.00189655 | 4.83247e-05 | 2.3095e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2214.39 | 0.0833101 | 1066.56ms | 8051 | 160 | 1335.08 | 3467.34 | 0.111992 | 2.35397 | 10.9986 | 1.72364 | 0.00121802 | 6.52093e-05 | 2.71705e-05 | 2(Loss) | true |
| simdjson (reflection) | 1962.39 | 0.049641 | 1117.66ms | 8051 | 4890 | 18446.6 | 3912.58 | 0.0258911 | 2.64359 | 10.4943 | 1.63769 | 0.00216915 | 8.33897e-05 | 5.02421e-05 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1650.3 | 0.060889 | 1191.87ms | 8051 | 2560 | 20544.4 | 4652.51 | 0.120229 | 3.13617 | 11.487 | 1.85344 | 0.00289585 | 4.36184e-05 | 1.72727e-05 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1649.53 | 0.145534 | 1199.6ms | 8051 | 320 | 14684.5 | 4654.68 | 0.0721871 | 3.2017 | 13.4874 | 2.59061 | 0.00343668 | 6.17159e-05 | 2.01838e-05 | 4(Tie) | true |
