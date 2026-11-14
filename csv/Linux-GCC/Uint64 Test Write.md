
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 947.949 | 0.0407856 | 1125.67ms | 3873 | 4890 | 12349.5 | 3896.39 | 0.0191312 | 5.36643 | 24.5474 | 5.13581 | 0.00677893 | 0.000106289 | 4.11321e-05 | 1(Win) | true |
| simdjson (reflection) | 896.152 | 0.192041 | 1146.68ms | 3873 | 40 | 2505.99 | 4121.6 | 0.0161776 | 5.69886 | 27.488 | 5.36251 | 0.010528 | 0.000154919 | 0.000109734 | 2(Loss) | true |
| Glaze | 860.904 | 0.0408089 | 1170.27ms | 3873 | 2560 | 7847.59 | 4290.35 | 0.155888 | 5.88682 | 28.8727 | 5.8629 | 0.00661874 | 0.000155524 | 8.09894e-05 | 3(Loss) | true |
