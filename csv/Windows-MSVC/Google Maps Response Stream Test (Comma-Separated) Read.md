
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 671.532 | 0.17954 | 9666.02ms | 4203058 | 40 | 4.59391e+09 | 5.96896e+06 | 0.337623 | 4.52577 | 1(Win) | true |
| simdjson (ondemand) | 531.95 | 0.442044 | 5565.57ms | 4203058 | 30 | 3.32844e+10 | 7.5352e+06 | 0.15285 | 5.71309 | 2(Loss) | true |
