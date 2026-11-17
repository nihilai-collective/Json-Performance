
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1023.08 | 0.263296 | 6348.05ms | 264040 | 640 | 2.68773e+08 | 246127 | 0.0884473 | 2.41954 | 1(Win) | true |
| simdjson (ondemand) | 874.265 | 0.142079 | 7410.25ms | 264040 | 1280 | 2.14349e+08 | 288023 | 0.0759251 | 2.83146 | 2(Loss) | true |
