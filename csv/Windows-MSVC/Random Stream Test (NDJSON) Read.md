
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 881.219 | 0.39203 | 8380ms | 4506447 | 30 | 1.09663e+10 | 4.87698e+06 | 0.173221 | 3.44881 | 1(Win) | true |
| simdjson (ondemand) | 746.096 | 0.124868 | 9819.07ms | 4506447 | 40 | 2.06938e+09 | 5.76022e+06 | 0.0892254 | 4.07346 | 2(Loss) | true |
