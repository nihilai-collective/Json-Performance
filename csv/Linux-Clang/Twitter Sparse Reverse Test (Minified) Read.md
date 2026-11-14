
----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4833.51 | 0.0313738 | 5933.49ms | 264040 | 1280 | 341947 | 52096.4 | 0.0459079 | 1.05721 | 5.31884 | 0.86493 | 0.00169293 | 4.73413e-06 | 2.21617e-06 | 1(Win) | true |
| simdjson (ondemand) | 3941.6 | 0.0321897 | 7144.03ms | 264040 | 2560 | 1.0826e+06 | 63884.7 | 0.0390657 | 1.283 | 6.37915 | 0.936322 | 0.00254018 | 4.52405e-06 | 1.32704e-06 | 2(Loss) | true |
