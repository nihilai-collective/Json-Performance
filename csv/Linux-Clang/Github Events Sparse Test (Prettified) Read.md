
----
### Github Events Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8522.53 | 0.101175 | 1467.79ms | 65103 | 320 | 17384.4 | 7285.05 | 0.0261169 | 0.607035 | 2.69806 | 0.356343 | 0.000714013 | 6.52812e-06 | 4.56008e-06 | 1(Win) | true |
| simdjson (ondemand) | 7609.81 | 0.035566 | 1556.9ms | 65103 | 1280 | 10777.9 | 8158.82 | 0.051882 | 0.679254 | 2.98485 | 0.352534 | 0.000752785 | 3.69607e-06 | 1.23602e-06 | 2(Loss) | true |
