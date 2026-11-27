
----
### Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3668.44 | 0.174234 | 7264.87ms | 277673 | 320 | 5.06196e+06 | 72185.9 | 0.0160202 | 0.828204 | 1(Win) | true |
| Jsonifier (generic) | 3519.59 | 0.0766027 | 7572.48ms | 277673 | 2560 | 8.50374e+06 | 75238.7 | 0.0356285 | 0.863285 | 2(Loss) | true |
