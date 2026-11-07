
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2243.1 | 0.0733408 | 40.9349ms | 905 | 320 | 25.4824 | 384.769 | 0.0308532 | 1.02979 | 1(Win) | true |
| Glaze | 211.44 | 0.128221 | 415.614ms | 905 | 40 | 1095.73 | 4081.9 | 0.0310217 | 11.6373 | 2(Loss) | true |
