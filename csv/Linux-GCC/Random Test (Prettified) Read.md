
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13273.9 | 0.0376333 | 5968.98ms | 728486 | 4890 | 1.89715e+06 | 52338.8 | 0.00485236 | 0.386049 | 1.84159 | 0.0690515 | 1.05022e-05 | 0.00106715 | 2.61573e-06 | 1(Win) | true |
| simdjson (stage-1) | 13061.3 | 0.0525261 | 6035.32ms | 728486 | 320 | 249789 | 53190.8 | 0.0473697 | 0.393171 | 1.96642 | 0.0748814 | 0.000221731 | 0.000726876 | 1.23973e-06 | 2(Loss) | true |
