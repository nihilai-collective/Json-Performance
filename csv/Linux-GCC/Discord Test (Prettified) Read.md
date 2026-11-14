
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2050.27 | 0.0596347 | 3970.66ms | 83958 | 4890 | 2.65221e+06 | 39052.7 | 0.593941 | 1.20671 | 1(Win) | true |
| simdjson (ondemand) | 1983.85 | 0.318482 | 4173.63ms | 83958 | 80 | 1.3218e+06 | 40360.2 | 0.0338091 | 1.24714 | 2(Loss) | true |
