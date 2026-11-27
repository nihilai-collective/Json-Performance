
----
### Canada Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1636.12 | 0.0623542 | 9530.08ms | 5212421 | 80 | 2.87125e+08 | 3.03826e+06 | 0.172989 | 1.51319 | 1(Win) | true |
| simdjson (ondemand) | 1438.01 | 0.159078 | 5162.84ms | 5212421 | 40 | 1.2096e+09 | 3.45684e+06 | 0.508121 | 1.72167 | 2(Loss) | true |
