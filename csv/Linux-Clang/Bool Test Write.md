
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2070.39 | 0.215401 | 43.9472ms | 905 | 30 | 24.1885 | 416.867 | 0.208333 | 1.11731 | 1(Win) | true |
| Glaze | 193.587 | 0.0579969 | 450.628ms | 905 | 30 | 200.575 | 4458.33 | 0.149757 | 12.7116 | 2(Loss) | true |
