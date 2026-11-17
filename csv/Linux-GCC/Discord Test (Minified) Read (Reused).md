
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1829.74 | 0.0555053 | 4003.58ms | 56369 | 160 | 42549.3 | 29380 | 0.00738118 | 2.81778 | 12.9451 | 2.5053 | 0.00570183 | 4.43506e-06 | 9.97889e-07 | 1(Win) | true |
| simdjson (ondemand) | 1507.87 | 0.0515737 | 4677.68ms | 56369 | 640 | 216365 | 35651.3 | 0.0043168 | 3.41217 | 13.6462 | 2.33469 | 0.010937 | 1.79897e-05 | 7.6782e-06 | 2(Loss) | true |
