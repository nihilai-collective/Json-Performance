
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1626.23 | 0.189114 | 9524.2ms | 5212421 | 30 | 1.00249e+09 | 3.05672e+06 | 1.32875 | 1.52238 | 1(Win) | true |
| simdjson (ondemand) | 1580.98 | 0.198901 | 9885.29ms | 5212421 | 80 | 3.12889e+09 | 3.14421e+06 | 1.74413 | 1.566 | 2(Loss) | true |
