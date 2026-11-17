
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 865.93 | 0.0570752 | 432.722ms | 3873 | 40 | 237.074 | 4265.45 | 0.100319 | 2.84082 | 1(Win) | true |
| Glaze | 781.861 | 0.264217 | 482.865ms | 3873 | 640 | 99709.9 | 4724.09 | 0.0836177 | 3.1483 | 2(Loss) | true |
