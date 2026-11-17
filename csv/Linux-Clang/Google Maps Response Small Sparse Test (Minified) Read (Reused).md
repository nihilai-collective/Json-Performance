
----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2257.16 | 0.0761532 | 907.299ms | 4390 | 80 | 159.615 | 1854.83 | 0.0794591 | 2.33207 | 10.4009 | 1.8959 | 0.00220387 | 1.70843e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2024.42 | 0.134866 | 931.959ms | 4390 | 30 | 233.375 | 2068.07 | 0.08227 | 2.59412 | 11.5733 | 1.83075 | 0.00220197 | 0 | 0 | 2(Loss) | true |
