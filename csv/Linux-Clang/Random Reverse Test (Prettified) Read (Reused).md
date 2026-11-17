
----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1387.19 | 0.0520272 | 6640.25ms | 676745 | 80 | 4.68739e+06 | 465253 | 0.170653 | 3.70717 | 16.7624 | 3.31189 | 0.00781555 | 0.0135819 | 0.000154157 | 1(Win) | true |
| simdjson (ondemand) | 784.035 | 0.0566548 | 5531.22ms | 676745 | 320 | 6.9599e+07 | 823171 | 0.0651328 | 6.50068 | 29.1422 | 5.20746 | 0.0226768 | 0.0233955 | 9.27694e-06 | 2(Loss) | true |
