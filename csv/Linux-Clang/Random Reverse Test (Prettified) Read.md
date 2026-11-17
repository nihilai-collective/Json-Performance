
----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1235.46 | 0.269534 | 6555.78ms | 676745 | 80 | 1.58603e+08 | 522393 | 0.0740891 | 2.0038 | 1(Win) | true |
| simdjson (ondemand) | 630.709 | 0.262263 | 6665.37ms | 676745 | 160 | 1.15235e+09 | 1.02328e+06 | 1.14911 | 3.92531 | 2(Loss) | true |
