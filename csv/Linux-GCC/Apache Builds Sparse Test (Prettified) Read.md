
----
### Apache Builds Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3416.26 | 0.0165388 | 4213.12ms | 124597 | 4890 | 161819 | 34782.2 | 0.0425796 | 1.48856 | 7.17579 | 1.26302 | 0.00291734 | 1.12986e-05 | 7.75835e-06 | 1(Win) | true |
| simdjson (ondemand) | 2444.77 | 0.0228565 | 5609.99ms | 124597 | 2560 | 315935 | 48603.8 | 0.0114338 | 2.07692 | 8.15313 | 1.45488 | 0.00673184 | 1.67415e-05 | 1.27223e-05 | 2(Loss) | true |
