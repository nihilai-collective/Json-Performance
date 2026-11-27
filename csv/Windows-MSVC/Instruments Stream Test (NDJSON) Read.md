
----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1306.6 | 0.598348 | 10368.2ms | 4197496 | 30 | 1.00815e+10 | 3.06371e+06 | 1.14882 | 2.32593 | 1(Win) | true |
| simdjson (ondemand) | 967.479 | 0.182324 | 6934.98ms | 4197496 | 40 | 2.27638e+09 | 4.1376e+06 | 1.93274 | 3.14107 | 2(Loss) | true |
