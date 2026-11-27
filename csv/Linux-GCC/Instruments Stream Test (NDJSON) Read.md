
----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1909.46 | 0.189938 | 6617.27ms | 4197496 | 160 | 2.53691e+09 | 2.09643e+06 | 0.0280306 | 1.29658 | 1(Win) | true |
| simdjson (ondemand) | 1744.05 | 0.273101 | 7341.58ms | 4197496 | 160 | 6.28678e+09 | 2.29525e+06 | 2.11017 | 1.41954 | 2(Loss) | true |
