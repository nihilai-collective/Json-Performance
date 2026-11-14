
----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1080.12 | 0.0307312 | 1060.06ms | 3770 | 2560 | 2678.78 | 3328.66 | 0.0484312 | 4.82608 | 19.9939 | 3.69576 | 0.00160716 | 3.9477e-05 | 2.90119e-06 | 1(Win) | true |
| simdjson (ondemand) | 481.714 | 0.0425069 | 1474.22ms | 3770 | 2560 | 25767 | 7463.67 | 0.0577137 | 10.7293 | 49.3501 | 8.41751 | 0.01093 | 4.75589e-05 | 8.80719e-06 | 2(Loss) | true |
