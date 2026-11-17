
----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 799.266 | 0.0513591 | 1308.19ms | 4926 | 2560 | 23328.2 | 5877.64 | 0.00284455 | 6.48995 | 27.4271 | 5.50569 | 0.00936429 | 0.000117124 | 6.71659e-05 | 1(Win) | true |
| simdjson (ondemand) | 499.343 | 0.0218006 | 1665.52ms | 4926 | 4890 | 20570.2 | 9407.97 | 0.096567 | 10.3364 | 45.3924 | 9.09217 | 0.0190933 | 6.23959e-05 | 2.45349e-05 | 2(Loss) | true |
