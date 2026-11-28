
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 330.821 | 0.034636 | 356.415ms | 1213 | 160 | 234.7 | 3496.78 | 0.432076 | 7.4296 | 1(Win) | true |
| Glaze | 266.558 | 0.319214 | 434.241ms | 1213 | 2560 | 491294 | 4339.79 | 0.377064 | 9.2335 | 2(Loss) | true |
