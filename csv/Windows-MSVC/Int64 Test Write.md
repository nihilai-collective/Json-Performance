
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 420.613 | 0.202198 | 891.282ms | 3862 | 2560 | 802514 | 8756.48 | 0.0944834 | 5.85764 | 1(Win) | true |
| Glaze | 350.353 | 0.108713 | 1138.57ms | 3862 | 40 | 5224.36 | 10512.5 | 0.481224 | 7.04377 | 2(Loss) | true |
