
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2405.2 | 0.101329 | 9820.72ms | 7351818 | 80 | 6.97978e+08 | 2.91503e+06 | 0.0658604 | 2.09691 | 8.5812 | 1.64695 | 0.0105228 | 0.0535552 | 0.00480047 | 1(Win) | true |
| simdjson (ondemand) | 2333.29 | 0.118432 | 10130.5ms | 7351818 | 80 | 1.01317e+09 | 3.00487e+06 | 0.044044 | 2.17364 | 8.98724 | 1.44229 | 0.010595 | 0.0537326 | 0.00534579 | 2(Loss) | true |
