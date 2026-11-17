
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2250.86 | 0.0633503 | 7790.74ms | 183677 | 2560 | 6.22231e+06 | 77822.9 | 0.0521245 | 1.34988 | 1(Win) | true |
| Jsonifier | 2095.66 | 0.0440347 | 8345.97ms | 183677 | 640 | 867041 | 83586.2 | 0.066218 | 1.44994 | 2(Loss) | true |
| Glaze | 1713.82 | 0.0456181 | 5240.78ms | 183677 | 640 | 1.39134e+06 | 102209 | 0.0425167 | 1.77308 | 3(Loss) | true |
| simdjson (ondemand) | 1363.85 | 0.0388895 | 6570.82ms | 183677 | 2560 | 6.38672e+06 | 128436 | 0.347068 | 2.2281 | 4(Loss) | true |
