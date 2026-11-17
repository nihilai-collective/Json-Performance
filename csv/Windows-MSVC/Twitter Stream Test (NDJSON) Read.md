
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1107.63 | 1.11063 | 6020.92ms | 4219120 | 80 | 1.30222e+11 | 3.63268e+06 | 1.9587 | 2.23522 | 1(Win) | true |
| simdjson (ondemand) | 1009.48 | 0.706503 | 6641.95ms | 4219120 | 80 | 6.34401e+10 | 3.98587e+06 | 0.38855 | 2.45255 | 2(Loss) | true |
