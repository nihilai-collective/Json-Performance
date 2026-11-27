
----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2452.63 | 0.0624499 | 1197.42ms | 11812 | 2560 | 21061.4 | 4592.95 | 0.0189538 | 2.11447 | 10.2116 | 1.82061 | 0.00321419 | 1.68327e-05 | 3.14167e-06 | 1(Win) | true |
| simdjson (ondemand) | 2111.19 | 0.122437 | 1270.57ms | 11812 | 320 | 13657.3 | 5335.77 | 0.190412 | 2.45494 | 11.2847 | 1.79402 | 0.00307341 | 1.21698e-05 | 2.38105e-06 | 2(Loss) | true |
