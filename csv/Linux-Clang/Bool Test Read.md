
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1016.62 | 0.0606507 | 91.9133ms | 905 | 160 | 42.4204 | 848.969 | 0.514281 | 2.35167 | 1(Win) | true |
| simdjson (stage-1) | 463.944 | 0.0703767 | 194.248ms | 905 | 80 | 137.124 | 1860.3 | 0.0282292 | 5.25454 | 2(Loss) | true |
