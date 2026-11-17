
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 841.054 | 0.15886 | 458.616ms | 3873 | 2560 | 124599 | 4391.61 | 0.200283 | 2.92572 | 1(Win) | true |
| simdjson (ondemand) | 606.768 | 0.0676644 | 640.085ms | 3873 | 40 | 678.626 | 6087.3 | 0.324213 | 4.06176 | 2(Loss) | true |
