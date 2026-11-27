
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2388.76 | 0.157034 | 6532.58ms | 631514 | 80 | 1.25399e+07 | 252122 | 0.162198 | 1(Win) | true |
| Jsonifier (two-stage) | 2020.53 | 0.263911 | 7616.1ms | 631514 | 30 | 1.8564e+07 | 298069 | 0.631543 | 2(Loss) | true |
| Glaze | 1951.11 | 0.171447 | 8007.74ms | 631514 | 80 | 2.24054e+07 | 308675 | 0.154706 | 3(Loss) | true |
| simdjson (reflection) | 1718.8 | 0.31351 | 9101.64ms | 631514 | 30 | 3.62027e+07 | 350396 | 0.153191 | 4(Loss) | true |
| simdjson (ondemand) | 1339.29 | 0.200203 | 5765.09ms | 631514 | 160 | 1.29682e+08 | 449686 | 0.301203 | 5(Loss) | true |
