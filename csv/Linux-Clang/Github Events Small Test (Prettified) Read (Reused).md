
----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1764.25 | 0.0563386 | 843.015ms | 2158 | 640 | 276.422 | 1166.52 | 0.0465915 | 3.02345 | 10.8689 | 2.019 | 0.000472805 | 6.51645e-05 | 1.52051e-05 | 1(Win) | true |
| simdjson (ondemand) | 1727.84 | 0.0364491 | 849.766ms | 2158 | 1280 | 241.257 | 1191.1 | 0.11282 | 3.08411 | 12.082 | 1.96339 | 0.000463392 | 7.63873e-05 | 1.66532e-05 | 2(Loss) | true |
