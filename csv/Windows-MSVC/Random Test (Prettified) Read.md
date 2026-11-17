
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1147.6 | 0.155194 | 7135.61ms | 676745 | 640 | 4.87523e+08 | 562385 | 0.106886 | 2.6482 | 1(Win) | true |
| simdjson (ondemand) | 982.612 | 0.0938861 | 8329.05ms | 676745 | 640 | 2.43371e+08 | 656815 | 0.0674636 | 3.09301 | 2(Loss) | true |
