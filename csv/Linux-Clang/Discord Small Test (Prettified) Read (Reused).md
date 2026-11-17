
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2393.52 | 0.126243 | 1020.59ms | 6701 | 640 | 7271.11 | 2669.94 | 0.0984721 | 2.17376 | 8.96687 | 1.61752 | 0.00143099 | 2.96131e-05 | 1.0726e-05 | 1(Win) | true |
| simdjson (ondemand) | 2193.94 | 0.111552 | 1054.36ms | 6701 | 320 | 3378.58 | 2912.83 | 0.0716097 | 2.37675 | 9.97314 | 1.55798 | 0.000705119 | 2.70482e-05 | 0 | 2(Loss) | true |
