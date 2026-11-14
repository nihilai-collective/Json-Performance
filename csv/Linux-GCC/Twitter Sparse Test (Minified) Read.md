
----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7544.65 | 0.104688 | 3394.28ms | 264040 | 2560 | 3.12532e+06 | 33375.7 | 0.35397 | 0.327875 | 1(Win) | true |
| simdjson (ondemand) | 6904.24 | 0.155112 | 3646.93ms | 264040 | 640 | 2.04822e+06 | 36471.5 | 0.61443 | 0.358327 | 2(Loss) | true |
