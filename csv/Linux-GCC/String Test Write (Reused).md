
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5316.71 | 0.0535994 | 84.7605ms | 4215 | 2560 | 420.406 | 756.057 | 0.157076 | 0.449042 | 1(Win) | true |
| simdjson (reflection) | 4112.84 | 0.0640995 | 109.307ms | 4215 | 80 | 31.3986 | 977.362 | 0.062708 | 0.585519 | 2(Loss) | true |
| Glaze | 2510.71 | 0.0770219 | 161.225ms | 4215 | 30 | 45.6195 | 1601.03 | 0.0229071 | 0.970249 | 3(Loss) | true |
