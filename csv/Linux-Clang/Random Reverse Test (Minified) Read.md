
----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 819.255 | 0.0964881 | 6145.02ms | 409725 | 160 | 3.38855e+07 | 476951 | 0.0164966 | 6.21561 | 28.815 | 5.82606 | 0.0133943 | 0.0152858 | 2.78235e-05 | 1(Win) | true |
| simdjson (ondemand) | 451.869 | 0.1307 | 5503.77ms | 409725 | 80 | 1.02188e+08 | 864729 | 0.165304 | 11.3222 | 50.5956 | 9.29805 | 0.0365147 | 0.0334486 | 5.18946e-05 | 2(Loss) | true |
