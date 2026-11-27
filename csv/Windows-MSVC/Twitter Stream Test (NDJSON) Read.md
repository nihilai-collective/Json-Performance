
----
### Twitter Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1355.5 | 0.527571 | 5131.5ms | 4219120 | 40 | 9.81e+09 | 2.96841e+06 | 0.200127 | 2.24209 | 1(Win) | true |
| simdjson (ondemand) | 1117.85 | 0.484554 | 6136.29ms | 4219120 | 40 | 1.21681e+10 | 3.59947e+06 | 0.516217 | 2.71882 | 2(Loss) | true |
