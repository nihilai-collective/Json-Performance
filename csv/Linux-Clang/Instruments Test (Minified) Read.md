
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23158.9 | 0.033348 | 451.57ms | 108313 | 80 | 176.992 | 4460.29 | 0.109137 | 0.106285 | 1(Win) | true |
| simdjson (stage-1) | 19852.9 | 0.0279419 | 526.492ms | 108313 | 80 | 169.088 | 5203.02 | 0.038454 | 0.124055 | 2(Loss) | true |
