
----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2402.26 | 0.0288884 | 1196.85ms | 11812 | 2560 | 4697.8 | 4689.25 | 0.0302379 | 2.16183 | 10.3452 | 1.89604 | 0.00302142 | 2.1661e-05 | 8.59825e-06 | 1(Win) | true |
| simdjson (ondemand) | 2093.92 | 0.0281 | 1265.66ms | 11812 | 640 | 1462.58 | 5379.76 | 0.148716 | 2.47922 | 11.5238 | 1.83322 | 0.00371934 | 2.19586e-05 | 1.00533e-05 | 2(Loss) | true |
