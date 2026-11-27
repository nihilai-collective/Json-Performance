
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2485.69 | 0.175815 | 6224.75ms | 631514 | 160 | 2.90335e+07 | 242290 | 0.0453486 | 0.995846 | 1(Win) | true |
| Jsonifier (two-stage) | 2199.28 | 0.0792699 | 6976.67ms | 631514 | 1280 | 6.0316e+07 | 273844 | 0.0981774 | 1.12554 | 2(Loss) | true |
| Glaze | 1896.51 | 0.0662877 | 8058.53ms | 631514 | 640 | 2.83599e+07 | 317562 | 0.173149 | 1.30527 | 3(Loss) | true |
| simdjson (ondemand) | 1225 | 0.0876309 | 6254.69ms | 631514 | 640 | 1.18792e+08 | 491640 | 0.288338 | 2.02088 | 4(Loss) | true |
