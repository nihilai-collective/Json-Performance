
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3065.96 | 0.275098 | 123.207ms | 3873 | 2560 | 28117.5 | 1204.71 | 0.0131304 | 0.790504 | 1(Win) | true |
| Glaze | 1449.87 | 0.0812725 | 259.046ms | 3873 | 30 | 128.602 | 2547.53 | 0.0143951 | 1.69012 | 2(Loss) | true |
| Jsonifier (two-stage) | 901.005 | 0.0534998 | 415.1ms | 3873 | 40 | 192.4 | 4099.4 | 0.00406547 | 2.73187 | 3(Loss) | true |
| simdjson (ondemand) | 665.317 | 0.0245136 | 561.803ms | 3873 | 80 | 148.164 | 5551.61 | 0.000225159 | 3.70361 | 4(Loss) | true |
