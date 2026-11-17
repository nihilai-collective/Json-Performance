
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 398.482 | 0.0781253 | 919.96ms | 3862 | 2560 | 133485 | 9242.81 | 0.0160624 | 7.60982 | 1(Win) | true |
| Glaze | 380.878 | 0.106317 | 991.419ms | 3862 | 80 | 8455.7 | 9670 | 0.10352 | 7.95987 | 2(Loss) | true |
