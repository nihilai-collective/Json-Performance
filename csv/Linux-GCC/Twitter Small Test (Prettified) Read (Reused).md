
----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3126.19 | 0.153295 | 839.052ms | 3770 | 40 | 124.328 | 1150.08 | 0.0732372 | 1.70612 | 6.43183 | 1.04881 | 0.000530504 | 1.32626e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2762.96 | 0.0724276 | 858.044ms | 3770 | 160 | 142.122 | 1301.27 | 0.00240156 | 1.92181 | 7.13369 | 1.10292 | 0.000530504 | 2.32095e-05 | 0 | 2(Loss) | true |
