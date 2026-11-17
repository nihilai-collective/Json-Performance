
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6188.28 | 0.103641 | 863.474ms | 9578 | 80 | 187.224 | 1476.06 | 0.0550148 | 0.855279 | 4.19044 | 0.318229 | 0.000777824 | 1.30507e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 3505.23 | 0.0386528 | 973.973ms | 9578 | 2560 | 2597.27 | 2605.9 | 0.0314289 | 1.49051 | 7.31009 | 0.547609 | 0.000835655 | 1.72107e-05 | 2.40623e-06 | 2(Loss) | true |
