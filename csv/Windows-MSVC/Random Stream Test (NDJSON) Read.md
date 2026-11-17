
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 897.706 | 0.851073 | 8269.5ms | 4506447 | 40 | 6.6404e+10 | 4.78741e+06 | 0.0626773 | 3.38554 | 1(Win) | true |
| simdjson (ondemand) | 728.939 | 0.522434 | 9931.88ms | 4506447 | 80 | 7.58996e+10 | 5.8958e+06 | 0.235466 | 4.16952 | 2(Loss) | true |
