
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1623.66 | 0.133144 | 9566.12ms | 5212421 | 80 | 1.3293e+09 | 3.06156e+06 | 0.0942379 | 1.5248 | 1(Win) | true |
| simdjson (ondemand) | 1570.18 | 0.161196 | 9886.13ms | 5212421 | 30 | 7.81286e+08 | 3.16585e+06 | 0.136859 | 1.57675 | 2(Loss) | true |
