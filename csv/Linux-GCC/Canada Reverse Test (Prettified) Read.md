
----
### Canada Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1717.74 | 0.0926601 | 8999.41ms | 5212421 | 30 | 2.15711e+08 | 2.89389e+06 | 0.201281 | 1.44131 | 1(Win) | true |
| simdjson (ondemand) | 1541.2 | 0.0865147 | 10075ms | 5212421 | 30 | 2.33594e+08 | 3.22538e+06 | 0.0180587 | 1.60641 | 2(Loss) | true |
