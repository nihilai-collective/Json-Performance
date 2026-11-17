
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 788.513 | 1.02485 | 9327.09ms | 4506446 | 80 | 2.49608e+11 | 5.45036e+06 | 0.38845 | 3.13982 | 1(Win) | true |
| simdjson (ondemand) | 630.221 | 1.60569 | 5333.23ms | 4506446 | 40 | 4.79586e+11 | 6.81932e+06 | 1.30123 | 3.92849 | 2(Loss) | true |
