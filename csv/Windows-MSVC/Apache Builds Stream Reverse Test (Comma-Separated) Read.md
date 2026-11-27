
----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 994.018 | 0.787611 | 7727.64ms | 4211999 | 30 | 3.03902e+10 | 4.04105e+06 | 0.439849 | 3.0575 | 1(Win) | true |
| simdjson (ondemand) | 821.083 | 0.424314 | 8902.28ms | 4211999 | 30 | 1.2927e+10 | 4.89217e+06 | 1.21418 | 3.70146 | 2(Loss) | true |
