
----
### Canada Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 716.934 | 0.101093 | 8753.18ms | 2090234 | 80 | 6.32064e+08 | 2.78045e+06 | 0.275507 | 3.45327 | 1(Win) | true |
| simdjson (ondemand) | 613.155 | 0.126708 | 10164.5ms | 2090234 | 80 | 1.35752e+09 | 3.25106e+06 | 0.103432 | 4.03776 | 2(Loss) | true |
