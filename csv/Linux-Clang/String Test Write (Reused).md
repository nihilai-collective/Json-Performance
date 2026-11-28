
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5721.74 | 0.111153 | 79.4232ms | 4215 | 80 | 48.7834 | 702.538 | 0.101521 | 0.416041 | 1(Win) | true |
| Glaze | 2101.14 | 0.149869 | 199.931ms | 4215 | 40 | 328.83 | 1913.12 | 0.00653424 | 1.16241 | 2(Loss) | true |
