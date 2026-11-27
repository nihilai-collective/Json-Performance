
----
### Random Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 808.18 | 0.634436 | 9390.03ms | 4506446 | 30 | 3.41467e+10 | 5.31773e+06 | 0.088681 | 3.76052 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 617.889 | 0.947844 | 5380.96ms | 4506446 | 40 | 1.73852e+11 | 6.95542e+06 | 5.3296 | 4.91851 | -(Loss) | false |
