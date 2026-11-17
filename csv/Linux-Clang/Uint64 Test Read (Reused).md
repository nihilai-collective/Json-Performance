
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 821.685 | 0.0534195 | 451.105ms | 3873 | 160 | 922.58 | 4495.13 | 0.118741 | 2.99476 | 1(Win) | true |
| simdjson (ondemand) | 617.28 | 0.0344458 | 608.202ms | 3873 | 80 | 339.854 | 5983.64 | 0.121642 | 3.99253 | 2(Loss) | true |
