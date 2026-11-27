
----
### Instruments Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 817.681 | 0.118216 | 7994.9ms | 4197496 | 30 | 1.00482e+09 | 4.89561e+06 | 1.24659 | 1(Win) | true |
| simdjson (ondemand) | 561.837 | 0.604134 | 10114.6ms | 4197496 | 30 | 5.55839e+10 | 7.12492e+06 | 1.26706 | 2(Loss) | true |
