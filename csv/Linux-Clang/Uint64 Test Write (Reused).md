
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2135.12 | 0.14942 | 64.9595ms | 1213 | 40 | 26.2154 | 541.8 | 0.202616 | 1.1006 | 1(Win) | true |
| Glaze | 1052.34 | 0.0904924 | 120.724ms | 1213 | 80 | 79.1639 | 1099.28 | 0.215586 | 2.29475 | 2(Loss) | true |
