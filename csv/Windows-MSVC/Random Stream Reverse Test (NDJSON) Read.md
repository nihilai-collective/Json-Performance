
----
### Random Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 569.492 | 1.00415 | 5844.29ms | 4506447 | 40 | 2.29695e+11 | 7.54652e+06 | 2.05539 | 5.33688 | 1(Win) | true |
| simdjson (ondemand) | 405.116 | 0.09389 | 8277.83ms | 4506447 | 40 | 3.96834e+09 | 1.06085e+07 | 0.71532 | 7.50246 | 2(Loss) | true |
