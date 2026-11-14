
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14889.3 | 0.0466336 | 1105.36ms | 56369 | 2560 | 7257.2 | 3610.49 | 0.0168318 | 0.343348 | 1.41947 | 0.224485 | 0.000177506 | 2.92991e-05 | 1.87104e-05 | 1(Win) | true |
| simdjson (reflection) | 13028.3 | 0.106037 | 1155.75ms | 56369 | 80 | 1531.47 | 4126.24 | 0.123145 | 0.392038 | 1.69984 | 0.277546 | 0.000161658 | 1.90708e-05 | 1.50792e-05 | 2(Loss) | true |
| Glaze | 6276.78 | 0.0864505 | 1596.01ms | 56369 | 1280 | 70170 | 8564.53 | 0.055631 | 0.808625 | 3.0545 | 0.466338 | 8.29495e-05 | 1.70057e-05 | 8.66223e-06 | 3(Loss) | true |
