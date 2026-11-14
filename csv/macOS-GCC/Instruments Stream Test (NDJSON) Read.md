
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1212.73 | 0.975063 | 5149.56ms | 4197496 | 40 | 4.14362e+10 | 3.30086e+06 | 0.411437 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 895.053 | 1.54412 | 7067.87ms | 4197496 | 40 | 1.90767e+11 | 4.47241e+06 | 8.75942 | -(Loss) | false |
