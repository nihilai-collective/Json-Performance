
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 424.519 | 0.164839 | 878.784ms | 3873 | 4890 | 1.00585e+06 | 8700.63 | 0.0546406 | 5.80206 | 1(Win) | true |
| Glaze | 333.556 | 0.0961717 | 1139.86ms | 3873 | 30 | 3402.3 | 11073.3 | 0.150739 | 7.40298 | 2(Loss) | true |
