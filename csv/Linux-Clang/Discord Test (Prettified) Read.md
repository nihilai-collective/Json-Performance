
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1975.48 | 0.0134235 | 4795.49ms | 83958 | 4890 | 144750 | 40531.2 | 0.244385 | 2.60158 | 11.059 | 2.09798 | 0.00513471 | 1.2924e-05 | 5.5559e-06 | 1(Win) | true |
| simdjson (ondemand) | 1772.18 | 0.0117676 | 5258.12ms | 83958 | 4890 | 138228 | 45180.9 | 0.054988 | 2.90451 | 11.865 | 1.9435 | 0.00789461 | 8.48121e-06 | 2.72802e-06 | 2(Loss) | true |
