
----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1191.94 | 0.596842 | 5613.16ms | 4219119 | 80 | 3.24745e+10 | 3.37572e+06 | 0.938415 | 2.54975 | 1(Win) | true |
| simdjson (ondemand) | 987.541 | 0.276229 | 6601.53ms | 4219119 | 80 | 1.01336e+10 | 4.07443e+06 | 0.334042 | 3.07757 | 2(Loss) | true |
