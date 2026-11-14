
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2842.86 | 0.032723 | 6183.96ms | 124597 | 1280 | 239453 | 41797.7 | 0.000194389 | 1.79187 | 8.79962 | 1.51452 | 0.00457495 | 2.27609e-06 | 1.88106e-07 | 1(Win) | true |
| simdjson (ondemand) | 2080.96 | 0.0221762 | 7665.88ms | 124597 | 2560 | 410491 | 57101.1 | 0.0220204 | 2.45884 | 9.51666 | 1.7155 | 0.00660147 | 3.13824e-06 | 5.7059e-07 | 2(Loss) | true |
