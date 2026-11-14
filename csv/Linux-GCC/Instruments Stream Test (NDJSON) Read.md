
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1781.74 | 0.103528 | 7183.24ms | 4197496 | 160 | 8.6562e+08 | 2.2467e+06 | 1.02918 | 1.38952 | 1(Win) | true |
| simdjson (ondemand) | 1770.79 | 0.163201 | 7184.55ms | 4197496 | 30 | 4.08335e+08 | 2.2606e+06 | 0.0968675 | 1.39812 | 2(Loss) | true |
