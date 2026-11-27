
----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4888.03 | 0.294388 | 788.137ms | 3370 | 30 | 112.397 | 657.5 | 0.126582 | 1.13177 | 4.83858 | 0.752522 | 0.000593472 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3760.28 | 0.102183 | 805.408ms | 3370 | 1280 | 976.314 | 854.691 | 0.0212934 | 1.43526 | 5.66944 | 0.830267 | 0.000594167 | 3.89466e-05 | 2.99054e-05 | 2(Loss) | true |
