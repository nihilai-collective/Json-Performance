
----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1953.54 | 0.0174429 | 8111.66ms | 124597 | 4890 | 550451 | 60825.4 | 0.0187375 | 2.59383 | 13.0456 | 2.51824 | 0.00562364 | 2.08065e-05 | 1.58433e-05 | 1(Win) | true |
| simdjson (ondemand) | 1056.85 | 0.0272792 | 6748.75ms | 124597 | 2560 | 2.40821e+06 | 112433 | 0.130305 | 4.8034 | 23.1629 | 4.67771 | 0.00868503 | 1.67446e-05 | 1.01201e-05 | 2(Loss) | true |
