
----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1060.12 | 0.144421 | 880.502ms | 1691 | 640 | 3089 | 1521.21 | 0.0960483 | 4.98273 | 19.0278 | 3.7605 | 0.00124556 | 0.000114577 | 2.67963e-05 | 1(Win) | true |
| simdjson (ondemand) | 742.002 | 0.168515 | 944.164ms | 1691 | 320 | 4292.43 | 2173.39 | 0.241276 | 7.0649 | 28.6334 | 5.0272 | 0.00186465 | 0.000120121 | 4.80485e-05 | 2(Loss) | true |
