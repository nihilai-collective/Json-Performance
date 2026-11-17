
----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12006.2 | 0.131192 | 805.948ms | 11579 | 80 | 116.475 | 919.737 | 0.0421138 | 0.447733 | 2.126 | 0.20874 | 0.000345453 | 2.15908e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 10725.8 | 0.0594654 | 817.641ms | 11579 | 4890 | 1832.81 | 1029.53 | 0.0367919 | 0.498483 | 2.45073 | 0.231626 | 0.000173133 | 6.32271e-06 | 4.94513e-07 | 2(Loss) | true |
