
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 799.149 | 0.215258 | 462.505ms | 3873 | 1280 | 126698 | 4621.89 | 0.16617 | 3.08066 | 1(Win) | true |
| simdjson (ondemand) | 555.882 | 0.132141 | 672.457ms | 3873 | 2560 | 197354 | 6644.54 | 0.0600948 | 4.43674 | 2(Loss) | true |
