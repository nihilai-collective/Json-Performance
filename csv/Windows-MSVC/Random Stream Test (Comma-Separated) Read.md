
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 732.338 | 3.53519 | 10343.2ms | 4506446 | 30 | 1.2912e+12 | 5.86844e+06 | 1.09154 | 3.38054 | 1(Win) | true |
| simdjson (ondemand) | 568.345 | 0.473005 | 6329.78ms | 4506446 | 30 | 3.83794e+10 | 7.56175e+06 | 2.09062 | 4.35605 | 2(Loss) | true |
