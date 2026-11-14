
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 825.004 | 0.367801 | 8904.2ms | 4506446 | 80 | 2.93679e+10 | 5.20929e+06 | 0.0586828 | 3.68388 | 1(Win) | true |
| simdjson (ondemand) | 648.475 | 0.469033 | 5145.91ms | 4506446 | 30 | 2.89874e+10 | 6.62737e+06 | 0.402273 | 4.68678 | 2(Loss) | true |
