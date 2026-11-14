
----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11668.9 | 0.302655 | 776.678ms | 4857 | 2560 | 3694.95 | 396.951 | 0.0849968 | 0.476312 | 1.57175 | 0.261684 | 0.000207014 | 2.75054e-05 | 4.66466e-06 | 1(Win) | true |
| Glaze | 3181.64 | 0.219548 | 878.887ms | 4857 | 2560 | 26153.9 | 1455.85 | 0.271841 | 1.62709 | 3.68581 | 0.525428 | 0.000211116 | 2.31624e-05 | 1.68893e-06 | 2(Loss) | true |
