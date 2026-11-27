
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2182.45 | 0.142246 | 43.6218ms | 905 | 80 | 25.315 | 395.462 | 0.0347815 | 1.0557 | 1(Win) | true |
| Glaze | 2158.05 | 0.200225 | 42.6294ms | 905 | 30 | 19.2368 | 399.933 | 0.091598 | 1.06582 | 2(Loss) | true |
| simdjson (reflection) | 1120.29 | 0.0981311 | 78.5933ms | 905 | 40 | 22.8615 | 770.4 | 0.357836 | 2.13298 | 3(Loss) | true |
| simdjson (ondemand) | 476.64 | 0.392367 | 186.034ms | 905 | 1280 | 64611.6 | 1810.75 | 0.169372 | 5.11271 | 4(Loss) | true |
