
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2784.64 | 0.0392414 | 1205.47ms | 9578 | 4890 | 8102.35 | 3280.24 | 0.0373727 | 1.8438 | 9.90228 | 1.76373 | 0.000209986 | 1.72088e-05 | 4.16343e-06 | 1(Win) | true |
| Glaze | 1912.68 | 0.048531 | 1365.98ms | 9578 | 4890 | 26267.1 | 4775.65 | 0.216368 | 2.66171 | 13.3648 | 2.54239 | 0.000153257 | 3.0361e-05 | 9.92817e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1741.19 | 0.0678219 | 1409.05ms | 9578 | 2560 | 32407.1 | 5246.02 | 0.15385 | 2.92949 | 14.7119 | 2.15995 | 0.000111665 | 2.06773e-05 | 6.6885e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1683.99 | 0.0309798 | 1418.26ms | 9578 | 4890 | 13808.2 | 5424.21 | 0.0448629 | 3.02451 | 15.4449 | 2.05199 | 0.00308811 | 3.81754e-05 | 1.5821e-05 | 4(Loss) | true |
