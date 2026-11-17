
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1612.8 | 0.131138 | 946.934ms | 3862 | 30 | 269.057 | 2283.67 | 0.0248077 | 3.25022 | 16.4606 | 1.99171 | 0.00159675 | 1.72622e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 803.045 | 0.071545 | 1179.67ms | 3862 | 320 | 3445.51 | 4586.41 | 0.0257621 | 6.46568 | 27.7962 | 3.39203 | 0.0165466 | 4.04583e-05 | 1.61833e-06 | 2(Loss) | true |
