
----
### Random Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 560.401 | 1.32443 | 5709.73ms | 4506446 | 40 | 4.1266e+11 | 7.66894e+06 | 7.01192 | 5.42344 | -(Win) | false |
| simdjson (ondemand) | 380.109 | 0.114822 | 8634ms | 4506446 | 30 | 5.05624e+09 | 1.13065e+07 | 0.0906624 | 7.99601 | 2(Loss) | true |
