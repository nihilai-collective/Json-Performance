
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 935.983 | 0.173587 | 399.373ms | 3873 | 2560 | 120125 | 3946.21 | 0.0928572 | 2.62805 | 1(Win) | true |
| Glaze | 844.228 | 0.361658 | 444.273ms | 3873 | 320 | 80116.6 | 4375.1 | 0.101181 | 2.9154 | 2(Loss) | true |
