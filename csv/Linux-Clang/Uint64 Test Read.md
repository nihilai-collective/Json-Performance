
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4688.85 | 0.0594799 | 85.1389ms | 3873 | 160 | 35.1256 | 787.737 | 0.0571583 | 0.509385 | 1(Win) | true |
| simdjson (stage-1) | 2124.58 | 0.0739648 | 178.203ms | 3873 | 80 | 132.278 | 1738.5 | 0.282649 | 1.14691 | 2(Loss) | true |
