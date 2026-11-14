
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1130.14 | 1.3282 | 6205.27ms | 4219120 | 40 | 8.94484e+10 | 3.56034e+06 | 1.40237 | 2.19068 | 1(Win) | true |
| simdjson (ondemand) | 932.948 | 0.926067 | 7200.32ms | 4219120 | 30 | 4.78559e+10 | 4.31285e+06 | 1.04445 | 2.65368 | 2(Loss) | true |
