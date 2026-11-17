
----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1073.11 | 0.989194 | 6268.03ms | 4219119 | 80 | 1.10055e+11 | 3.74955e+06 | 0.859494 | 2.30713 | 1(Win) | true |
| simdjson (ondemand) | 931.377 | 0.595372 | 7192.14ms | 4219119 | 30 | 1.98469e+10 | 4.32013e+06 | 1.43778 | 2.65823 | 2(Loss) | true |
