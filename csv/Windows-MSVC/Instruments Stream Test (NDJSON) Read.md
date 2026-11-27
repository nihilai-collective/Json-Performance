
----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1452.35 | 0.197516 | 9417.37ms | 4197496 | 30 | 8.89123e+08 | 2.75625e+06 | 1.5939 | 1.70461 | 1(Win) | true |
| simdjson (ondemand) | 951.34 | 0.10907 | 6669.7ms | 4197496 | 40 | 8.42525e+08 | 4.2078e+06 | 0.52923 | 2.6023 | 2(Loss) | true |
