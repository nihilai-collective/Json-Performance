
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1912.37 | 0.128438 | 4114.83ms | 83958 | 4890 | 1.41408e+07 | 41868.8 | 0.348241 | 1.29376 | 1(Win) | true |
| simdjson (ondemand) | 1857.07 | 0.310147 | 4163.85ms | 83958 | 160 | 2.86102e+06 | 43115.5 | 0.00672567 | 1.33231 | 2(Loss) | true |
