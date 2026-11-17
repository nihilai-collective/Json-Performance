
----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 834.811 | 0.0743391 | 1339.53ms | 4630 | 4890 | 75601.3 | 5289.23 | 0.0761957 | 6.19567 | 31.0765 | 5.64428 | 0.00284183 | 8.34338e-05 | 3.97073e-05 | 1(Win) | true |
| Jsonifier (generic) | 765.611 | 0.100425 | 1387.08ms | 4630 | 640 | 21469.1 | 5767.31 | 0.162357 | 6.76636 | 29.9302 | 6.00886 | 0.00833255 | 0.000195397 | 0.000136677 | 2(Loss) | true |
