
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1395.42 | 0.454309 | 6308.61ms | 360584 | 160 | 2.00552e+08 | 246434 | 0.00634003 | 2.17774 | 1(Win) | true |
| simdjson (ondemand) | 1236.75 | 0.155913 | 7077.79ms | 360584 | 1280 | 2.40561e+08 | 278051 | 0.0509945 | 2.45708 | 2(Loss) | true |
