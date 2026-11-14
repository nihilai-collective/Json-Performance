
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1447.24 | 0.0791382 | 3882.92ms | 56369 | 2560 | 2.21214e+06 | 37145 | 0.173462 | 1.70949 | 1(Win) | true |
| simdjson (ondemand) | 1413.83 | 0.359675 | 3852.19ms | 56369 | 40 | 748114 | 38022.8 | 0.0838359 | 1.74985 | 2(Loss) | true |
