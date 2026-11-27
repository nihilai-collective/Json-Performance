
----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2310.53 | 0.0904087 | 909.388ms | 4390 | 160 | 429.383 | 1811.97 | 0.0648043 | 2.27933 | 10.2645 | 1.82164 | 0.00224943 | 1.70843e-05 | 7.11845e-06 | 1(Win) | true |
| simdjson (ondemand) | 2026.38 | 0.0945773 | 933.131ms | 4390 | 30 | 114.547 | 2066.07 | 0.0789928 | 2.54509 | 11.354 | 1.79339 | 0.00136674 | 0 | 0 | 2(Loss) | true |
