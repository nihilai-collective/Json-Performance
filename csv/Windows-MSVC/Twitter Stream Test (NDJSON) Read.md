
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1238.05 | 0.876849 | 5444.59ms | 4219120 | 80 | 6.49689e+10 | 3.25e+06 | 0.180634 | 2.45479 | 1(Win) | true |
| simdjson (ondemand) | 1069.71 | 0.727139 | 6145.65ms | 4219120 | 80 | 5.98467e+10 | 3.76147e+06 | 0.832575 | 2.84107 | 2(Loss) | true |
