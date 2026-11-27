
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 608.246 | 0.0869065 | 197.63ms | 1213 | 320 | 874.216 | 1901.88 | 0.652955 | 4.01872 | 1(Win) | true |
| Glaze | 121.052 | 0.144005 | 974.121ms | 1213 | 80 | 15150.3 | 9556.25 | 0.117586 | 20.3616 | 2(Loss) | true |
