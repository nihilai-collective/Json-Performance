
----
### Canada Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 711.98 | 0.0370969 | 1345.05ms | 4630 | 4890 | 25882.8 | 6201.74 | 0.251415 | 7.22833 | 35.1838 | 6.92894 | 0.00330524 | 0.000115897 | 4.21807e-05 | 1(Win) | true |
| simdjson (ondemand) | 684.528 | 0.131286 | 1362.92ms | 4630 | 40 | 2868.66 | 6450.45 | 0.00387585 | 7.57374 | 36.7164 | 6.63888 | 0.00451944 | 4.85961e-05 | 0 | 2(Loss) | true |
