
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1417.65 | 0.169963 | 6197.17ms | 360584 | 1280 | 2.17567e+08 | 242570 | 0.27311 | 2.14366 | 1(Win) | true |
| simdjson (ondemand) | 1238.86 | 0.233029 | 7047.28ms | 360584 | 640 | 2.67775e+08 | 277578 | 0.184466 | 2.45307 | 2(Loss) | true |
