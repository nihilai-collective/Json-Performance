
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1084.14 | 0.178298 | 5918.73ms | 264040 | 1280 | 2.19517e+08 | 232265 | 0.124474 | 2.80316 | 1(Win) | true |
| simdjson (ondemand) | 935.472 | 0.160334 | 6821.22ms | 264040 | 1280 | 2.38419e+08 | 269178 | 0.193878 | 3.24869 | 2(Loss) | true |
