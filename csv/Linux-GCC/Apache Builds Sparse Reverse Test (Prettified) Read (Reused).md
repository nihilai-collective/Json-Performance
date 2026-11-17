
----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2772.63 | 0.0248431 | 5503.22ms | 124597 | 1280 | 145095 | 42856.4 | 0.000242453 | 1.82552 | 8.69081 | 1.60163 | 0.00483377 | 2.66484e-06 | 6.27022e-07 | 1(Win) | true |
| simdjson (ondemand) | 2432.44 | 0.0435893 | 6124.58ms | 124597 | 640 | 290182 | 48850.1 | 0.00318247 | 2.09143 | 8.71778 | 1.53843 | 0.00617264 | 9.01657e-06 | 5.63065e-06 | 2(Loss) | true |
