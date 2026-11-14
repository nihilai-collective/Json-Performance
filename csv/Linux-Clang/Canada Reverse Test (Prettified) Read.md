
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1506.32 | 0.0833151 | 10117.6ms | 5212421 | 160 | 1.20952e+09 | 3.30007e+06 | 1.49223 | 1.64356 | 1(Win) | true |
| simdjson (ondemand) | 1385.63 | 0.155228 | 5399.46ms | 5212421 | 40 | 1.24046e+09 | 3.58749e+06 | 0.337305 | 1.78665 | 2(Loss) | true |
