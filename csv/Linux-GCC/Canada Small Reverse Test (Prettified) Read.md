
----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1697.28 | 0.0289528 | 1374.89ms | 11579 | 4890 | 17351.1 | 6506.07 | 0.0242409 | 3.05528 | 15.1046 | 2.71949 | 0.00161699 | 1.94097e-05 | 6.79956e-06 | 1(Win) | true |
| Jsonifier (generic) | 1560.56 | 0.191655 | 1422.53ms | 11579 | 160 | 29426.8 | 7076.04 | 0.163228 | 3.31233 | 14.7257 | 2.88263 | 0.00297251 | 3.88635e-05 | 2.91476e-05 | 2(Loss) | true |
