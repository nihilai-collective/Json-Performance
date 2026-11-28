
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 345.847 | 0.310643 | 336.827ms | 1213 | 1280 | 138193 | 3344.85 | 0.0852782 | 7.09984 | 1(Win) | true |
| simdjson (reflection) | 338.228 | 0.0922184 | 347.115ms | 1213 | 30 | 298.441 | 3420.2 | 0 | 7.25982 | 2(Loss) | true |
| Glaze | 278.207 | 0.240121 | 419.307ms | 1213 | 1280 | 127602 | 4158.08 | 0.256578 | 8.83921 | 3(Loss) | true |
