
----
### Canada Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1646.9 | 0.0304082 | 1398.73ms | 11579 | 4890 | 20328.2 | 6705.08 | 0.0291951 | 3.14428 | 14.8526 | 2.82313 | 0.00159228 | 2.97591e-05 | 1.14091e-05 | 1(Win) | true |
| simdjson (ondemand) | 1642.15 | 0.0868707 | 1402.57ms | 11579 | 4890 | 166868 | 6724.49 | 0.857353 | 3.1384 | 15.412 | 2.68909 | 0.00165491 | 6.48342e-05 | 3.09071e-05 | 2(Loss) | true |
