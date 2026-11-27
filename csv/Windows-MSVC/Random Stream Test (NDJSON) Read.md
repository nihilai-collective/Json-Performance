
----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 826.03 | 1.02607 | 8887.62ms | 4506447 | 40 | 1.13996e+11 | 5.20282e+06 | 0.24921 | 3.67931 | 1(Win) | true |
| simdjson (ondemand) | 689.515 | 0.606396 | 10542.4ms | 4506447 | 80 | 1.14284e+11 | 6.2329e+06 | 1.48896 | 4.40744 | 2(Loss) | true |
