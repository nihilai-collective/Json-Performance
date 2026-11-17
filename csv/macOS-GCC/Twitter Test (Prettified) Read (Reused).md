
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2608.46 | 0.511162 | 7080.33ms | 631514 | 30 | 4.17864e+07 | 230886 | 0.17401 | 1(Win) | true |
| Jsonifier (two-stage) | 2497.5 | 0.158438 | 7340ms | 631514 | 640 | 9.34234e+07 | 241144 | 0.288618 | 2(Loss) | true |
| Glaze | 2235.77 | 0.255177 | 8144.34ms | 631514 | 320 | 1.51197e+08 | 269374 | 0.746352 | 3(Loss) | true |
| simdjson (reflection) | 1715.95 | 1.05781 | 9790.52ms | 631514 | 40 | 5.51353e+08 | 350976 | 0.716924 | 4(Loss) | true |
| simdjson (ondemand) | 1451.67 | 0.342153 | 5893.72ms | 631514 | 30 | 6.04495e+07 | 414874 | 0.154502 | 5(Loss) | true |
