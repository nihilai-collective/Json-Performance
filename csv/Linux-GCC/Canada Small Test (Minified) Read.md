
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 795.764 | 0.0705199 | 1273.76ms | 4630 | 640 | 9799.33 | 5548.77 | 0.0282237 | 6.51519 | 31.4104 | 5.75616 | 0.00386373 | 3.03726e-05 | 1.11366e-05 | 1(Win) | true |
| Jsonifier (generic) | 677.442 | 0.0335232 | 1374.98ms | 4630 | 4890 | 23346.3 | 6517.92 | 0.0758223 | 7.69052 | 31.9069 | 6.44946 | 0.0102695 | 5.94063e-05 | 1.98757e-05 | 2(Loss) | true |
