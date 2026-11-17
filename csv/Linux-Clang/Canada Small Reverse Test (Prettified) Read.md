
----
### Canada Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1588.16 | 0.0260745 | 1420.35ms | 11579 | 4890 | 16072.9 | 6953.08 | 0.0336981 | 3.25936 | 15.5597 | 2.91951 | 0.00259915 | 9.33218e-05 | 5.54738e-05 | 1(Win) | true |
| simdjson (ondemand) | 1586.6 | 0.0312262 | 1422.15ms | 11579 | 4890 | 23096.9 | 6959.91 | 0.054133 | 3.24503 | 15.6882 | 2.7473 | 0.00168553 | 3.48985e-05 | 1.17447e-05 | 2(Loss) | true |
