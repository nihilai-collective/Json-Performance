
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2124.52 | 0.0328662 | 1348.15ms | 11579 | 2560 | 7470.67 | 5197.69 | 0.1996 | 2.40769 | 11.6789 | 1.8683 | 0.00133209 | 2.44246e-05 | 7.21943e-06 | 1(Win) | true |
| Jsonifier (generic) | 2026.42 | 0.0237083 | 1375.01ms | 11579 | 4890 | 8161.95 | 5449.31 | 0.0139989 | 2.52146 | 11.9963 | 2.15235 | 0.00187693 | 2.21118e-05 | 6.04013e-06 | 2(Loss) | true |
