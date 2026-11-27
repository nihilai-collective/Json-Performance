
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 659.037 | 0.0725859 | 178.447ms | 1213 | 30 | 48.7 | 1755.3 | 0.0379946 | 3.69876 | 1(Win) | true |
| simdjson (ondemand) | 318.199 | 0.171647 | 369.988ms | 1213 | 2560 | 99686.8 | 3635.49 | 0.221667 | 7.72674 | 2(Loss) | true |
