
----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1012.42 | 0.764789 | 7191.74ms | 4219119 | 80 | 7.39083e+10 | 3.97429e+06 | 1.24773 | 2.44535 | 1(Win) | true |
| simdjson (ondemand) | 809.854 | 0.5237 | 8647.57ms | 4219119 | 80 | 5.41608e+10 | 4.96838e+06 | 0.405009 | 3.05701 | 2(Loss) | true |
