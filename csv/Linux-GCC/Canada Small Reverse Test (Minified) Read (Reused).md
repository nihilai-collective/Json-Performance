
----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 829.147 | 0.0783014 | 1352.05ms | 4630 | 2560 | 44512.1 | 5325.37 | 0.134083 | 6.24723 | 31.1821 | 5.66436 | 0.0028978 | 4.17623e-05 | 1.19803e-05 | 1(Win) | true |
| Jsonifier (generic) | 738.742 | 0.0916055 | 1421.32ms | 4630 | 30 | 899.375 | 5977.07 | 0.0217451 | 7.15 | 30.265 | 6.04924 | 0.00945284 | 2.87977e-05 | 0 | 2(Loss) | true |
