
----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2815.4 | 0.182676 | 814.698ms | 2632 | 40 | 106.1 | 891.55 | 0.403544 | 1.87979 | 8.04749 | 1.48062 | 0.00113982 | 1.8997e-05 | 1.8997e-05 | 1(Win) | true |
| simdjson (ondemand) | 2408.21 | 0.107152 | 826.13ms | 2632 | 1280 | 1596.61 | 1042.3 | 0.166752 | 2.2048 | 9.07257 | 1.46277 | 0.00114219 | 2.34494e-05 | 7.12386e-06 | 2(Loss) | true |
