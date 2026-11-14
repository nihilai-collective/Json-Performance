
----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 641.427 | 0.0717589 | 10000ms | 264040 | 1280 | 1.0158e+08 | 392575 | 0.0335942 | 3.85946 | 1(Win) | true |
| simdjson (ondemand) | 251.103 | 0.0949934 | 6497.72ms | 264040 | 30 | 2.72235e+07 | 1.00281e+06 | 0.831481 | 9.85936 | 2(Loss) | true |
