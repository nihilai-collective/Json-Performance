
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1707.09 | 0.098647 | 70.1048ms | 1213 | 80 | 35.7494 | 677.65 | 0.0184495 | 1.39289 | 1(Win) | true |
| simdjson (reflection) | 1050.04 | 0.150154 | 113.096ms | 1213 | 40 | 109.456 | 1101.67 | 0.0582786 | 2.29773 | 2(Loss) | true |
| Glaze | 936.066 | 0.0526905 | 137.847ms | 1213 | 640 | 271.364 | 1235.82 | 0.0736571 | 2.57851 | 3(Loss) | true |
| simdjson (ondemand) | 321.563 | 0.136321 | 371.838ms | 1213 | 40 | 961.997 | 3597.45 | 0.239871 | 7.6434 | 4(Loss) | true |
