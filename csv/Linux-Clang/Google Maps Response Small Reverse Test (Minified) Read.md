
----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 765.877 | 0.0547632 | 1269.96ms | 4390 | 1280 | 11470.9 | 5466.45 | 0.0234329 | 6.77173 | 29.7517 | 5.95923 | 0.0121396 | 7.31421e-05 | 2.24231e-05 | 1(Win) | true |
| simdjson (ondemand) | 675.658 | 0.03759 | 1343.17ms | 4390 | 2560 | 13888.6 | 6196.37 | 0.125596 | 7.61838 | 33.2314 | 6.11276 | 0.00803655 | 0.000107311 | 4.66259e-05 | 2(Loss) | true |
