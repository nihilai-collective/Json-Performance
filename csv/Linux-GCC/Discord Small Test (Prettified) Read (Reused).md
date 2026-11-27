
----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2707.61 | 0.0563914 | 982.092ms | 6701 | 1280 | 2267.47 | 2360.22 | 0.117337 | 1.94275 | 8.21266 | 1.44456 | 0.000873237 | 6.70376e-05 | 3.05458e-05 | 1(Win) | true |
| simdjson (ondemand) | 2303.06 | 0.0501608 | 1028.14ms | 6701 | 640 | 1239.88 | 2774.82 | 0.160289 | 2.26976 | 9.30995 | 1.54664 | 0.00055682 | 2.77477e-05 | 7.46157e-06 | 2(Loss) | true |
