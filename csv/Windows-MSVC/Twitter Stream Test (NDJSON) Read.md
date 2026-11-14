
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1251.35 | 0.631257 | 5427.8ms | 4219120 | 80 | 3.29599e+10 | 3.21545e+06 | 0.31552 | 2.4286 | 1(Win) | true |
| simdjson (ondemand) | 1096.08 | 0.355057 | 6056.28ms | 4219120 | 80 | 1.35908e+10 | 3.67096e+06 | 0.45357 | 2.7727 | 2(Loss) | true |
