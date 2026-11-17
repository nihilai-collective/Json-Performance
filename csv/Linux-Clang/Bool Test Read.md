
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 378.604 | 0.0618317 | 235.117ms | 905 | 40 | 79.4712 | 2279.62 | 0.232669 | 6.4611 | 1(Win) | true |
| simdjson (ondemand) | 244.111 | 0.170185 | 372.252ms | 905 | 4890 | 177040 | 3535.58 | 0.227332 | 10.0621 | 2(Loss) | true |
