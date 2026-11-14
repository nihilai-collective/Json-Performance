
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2274.65 | 0.0838356 | 918.511ms | 4390 | 4890 | 11643 | 1840.56 | 0.00204276 | 2.27396 | 10.4692 | 1.85672 | 0.00160171 | 5.62256e-05 | 2.22666e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1716.1 | 0.0916949 | 983.352ms | 4390 | 4890 | 24470.4 | 2439.61 | 0.157411 | 2.97924 | 13.9068 | 2.39977 | 0.00258945 | 7.40202e-05 | 2.39436e-05 | 2(Loss) | true |
| Glaze | 1704.04 | 0.0679617 | 983.74ms | 4390 | 4890 | 13633.6 | 2456.89 | 0.00527421 | 3.00455 | 13.7622 | 2.65148 | 0.000732283 | 3.80582e-05 | 9.27e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1074.03 | 0.0744537 | 1126.11ms | 4390 | 4890 | 41188.5 | 3898.05 | 0.000593861 | 4.74214 | 20.4023 | 3.38474 | 0.00319228 | 6.51229e-05 | 1.41612e-05 | 4(Loss) | true |
