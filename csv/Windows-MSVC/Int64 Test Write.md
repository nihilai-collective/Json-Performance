
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 419.121 | 0.202627 | 909.847ms | 3862 | 2560 | 811673 | 8787.66 | 0.68747 | 5.8835 | 1(Win) | true |
| Glaze | 299.634 | 0.819462 | 1251.25ms | 3862 | 4890 | 4.96147e+07 | 12292 | 0.592079 | 8.24079 | 2(Loss) | true |
