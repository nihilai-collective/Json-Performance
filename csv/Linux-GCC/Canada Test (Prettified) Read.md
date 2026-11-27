
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1684.18 | 0.138589 | 9511.76ms | 5373214 | 40 | 7.1122e+08 | 3.0426e+06 | 0.436252 | 1.47001 | 1(Win) | true |
| Jsonifier (two-stage) | 1665.06 | 0.10406 | 9507.68ms | 5373214 | 160 | 1.64095e+09 | 3.07754e+06 | 0.774801 | 1.48687 | 2(Loss) | true |
| simdjson (reflection) | 1625.42 | 0.25485 | 10156.2ms | 5373214 | 30 | 1.93654e+09 | 3.15259e+06 | 0.884621 | 1.52316 | 3(Loss) | true |
| simdjson (ondemand) | 1549.65 | 0.121705 | 10320.9ms | 5373214 | 40 | 6.47856e+08 | 3.30674e+06 | 0.00196791 | 1.59761 | 4(Loss) | true |
| Glaze | 1476.72 | 0.313292 | 5078.69ms | 5373214 | 40 | 4.7275e+09 | 3.47006e+06 | 0.616246 | 1.67651 | 5(Loss) | true |
