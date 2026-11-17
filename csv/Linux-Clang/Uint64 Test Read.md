
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4707.07 | 0.224009 | 81.6921ms | 3873 | 80 | 247.18 | 784.688 | 0.0940749 | 0.506997 | 1(Win) | true |
| simdjson (stage-1) | 2219.37 | 0.0727914 | 169.9ms | 3873 | 80 | 117.405 | 1664.25 | 0.105263 | 1.09749 | 2(Loss) | true |
