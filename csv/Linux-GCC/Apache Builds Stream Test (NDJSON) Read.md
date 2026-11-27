
----
### Apache Builds Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1777.52 | 0.145383 | 8819.69ms | 4212000 | 80 | 8.63514e+08 | 2.25983e+06 | 0.00170591 | 1.39282 | 1(Win) | true |
| simdjson (ondemand) | 1692.45 | 0.0949447 | 9320.15ms | 4212000 | 30 | 1.52338e+08 | 2.37341e+06 | 0.00630277 | 1.46283 | 2(Loss) | true |
