
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 891.703 | 0.040148 | 1319.5ms | 4630 | 1280 | 5058.94 | 4951.78 | 0.0144855 | 5.82268 | 29.2235 | 5.47257 | 0.00374494 | 4.23529e-05 | 5.39957e-06 | 1(Win) | true |
| simdjson (ondemand) | 885.431 | 0.0965726 | 1320.86ms | 4630 | 640 | 14843.7 | 4986.85 | 0.00372842 | 5.85833 | 28.4724 | 4.76177 | 0.00237379 | 4.55589e-05 | 6.41199e-06 | 2(Loss) | true |
