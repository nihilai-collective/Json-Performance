
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2715.35 | 0.150894 | 1015.16ms | 8051 | 80 | 1456.41 | 2827.64 | 0.205096 | 1.89037 | 8.53571 | 1.64327 | 0.00170941 | 0.000111787 | 5.12359e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2111.84 | 0.15155 | 1098.89ms | 8051 | 30 | 910.769 | 3635.7 | 0.0412746 | 2.42138 | 11.0148 | 1.78624 | 0.00170165 | 7.03846e-05 | 4.5543e-05 | 2(Loss) | true |
| Glaze | 1423.52 | 0.0431146 | 1273.77ms | 8051 | 4890 | 26444 | 5393.69 | 0.0921874 | 3.57827 | 13.1828 | 2.56962 | 0.00276034 | 0.000100357 | 4.79306e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1291.78 | 0.0532959 | 1330.98ms | 8051 | 4890 | 49070.5 | 5943.77 | 0.112908 | 3.93993 | 14.8707 | 2.42989 | 0.00340795 | 7.21627e-05 | 3.13949e-05 | 4(Loss) | true |
