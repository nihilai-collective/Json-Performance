
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 506.148 | 0.0483226 | 737.073ms | 3862 | 4890 | 60461.6 | 7276.71 | 0.265172 | 5.98763 | 1(Win) | true |
| Glaze | 436.334 | 0.224864 | 857.306ms | 3862 | 4890 | 1.76172e+06 | 8440.98 | 0.0165974 | 6.94576 | 2(Loss) | true |
