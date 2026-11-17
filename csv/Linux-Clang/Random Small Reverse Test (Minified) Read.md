
----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 808.514 | 0.0333347 | 1305.7ms | 4926 | 4890 | 18344.9 | 5810.41 | 0.0750309 | 6.40712 | 27.3792 | 5.4996 | 0.0101167 | 0.000139986 | 6.23128e-05 | 1(Win) | true |
| simdjson (ondemand) | 458.085 | 0.0350367 | 1752.61ms | 4926 | 1280 | 16525.5 | 10255.3 | 0.0180514 | 11.2859 | 49.2385 | 8.96407 | 0.0248953 | 4.17111e-05 | 1.07846e-05 | 2(Loss) | true |
