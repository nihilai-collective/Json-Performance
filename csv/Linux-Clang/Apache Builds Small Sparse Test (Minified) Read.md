
----
### Apache Builds Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3190.28 | 0.199374 | 794.23ms | 2632 | 80 | 196.853 | 786.788 | 0.160721 | 1.69469 | 6.7728 | 1.19301 | 0.000569909 | 1.8997e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2433.31 | 0.115436 | 820.704ms | 2632 | 2560 | 3629.91 | 1031.55 | 0.12749 | 2.1886 | 8.23176 | 1.34726 | 0.00226242 | 2.18168e-05 | 5.19448e-06 | 2(Loss) | true |
