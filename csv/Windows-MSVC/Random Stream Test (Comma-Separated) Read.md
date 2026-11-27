
----
### Random Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 621.529 | 2.02994 | 7169.24ms | 4506446 | 30 | 5.91059e+11 | 6.91469e+06 | 0.211036 | 3.98325 | 1(Win) | true |
| simdjson (ondemand) | 540.437 | 1.50799 | 7814.96ms | 4506446 | 40 | 5.75224e+11 | 7.95224e+06 | 1.06901 | 4.58101 | 2(Loss) | true |
