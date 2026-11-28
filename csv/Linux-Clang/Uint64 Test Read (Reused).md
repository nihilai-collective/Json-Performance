
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1767.11 | 0.155797 | 68.745ms | 1213 | 30 | 31.2057 | 654.633 | 0.101735 | 1.34248 | 1(Win) | true |
| Glaze | 960.753 | 0.0554252 | 123.65ms | 1213 | 80 | 35.629 | 1204.06 | 0.0176517 | 2.51795 | 2(Loss) | true |
| simdjson (ondemand) | 307.923 | 0.303087 | 382.054ms | 1213 | 640 | 82976 | 3756.81 | 0.0253354 | 7.98233 | 3(Loss) | true |
