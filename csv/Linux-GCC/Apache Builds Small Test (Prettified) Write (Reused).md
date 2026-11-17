
----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18304.7 | 0.172075 | 743.477ms | 3643 | 30 | 3.2 | 189.8 | 0.0702988 | 0.336307 | 1.13752 | 0.173758 | 0.000274499 | 1.82999e-05 | 0 | 1(Win) | true |
| Glaze | 4639.72 | 0.0802503 | 803.408ms | 3682 | 4890 | 1803.79 | 756.819 | 0.108752 | 1.1495 | 3.92205 | 0.637154 | 0.000273535 | 3.40461e-05 | 1.19967e-05 | 2(Loss) | true |
| simdjson (reflection) | 540.057 | 0.089359 | 1387.75ms | 3643 | 2560 | 84597.2 | 6433.09 | 0.204959 | 9.34658 | 36.1112 | 7.56712 | 0.0150768 | 0.000349879 | 0.000196009 | 3(Loss) | true |
