
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4298.8 | 0.081951 | 940.944ms | 9578 | 640 | 1940.63 | 2124.85 | 0.246063 | 1.22072 | 5.4691 | 1.10221 | 0.00207556 | 1.5824e-05 | 3.26269e-07 | 1(Win) | true |
| simdjson (reflection) | 4090.61 | 0.0779619 | 944.587ms | 9578 | 2560 | 7758.51 | 2232.99 | 0.454893 | 1.27584 | 6.21549 | 1.15713 | 0.000595073 | 3.69499e-05 | 1.32139e-05 | 2(Loss) | true |
| Glaze | 2116.87 | 0.0397543 | 1147.33ms | 9578 | 2560 | 7533.03 | 4315 | 0.0361334 | 2.4468 | 12.7155 | 2.63771 | 0.00107412 | 3.17296e-05 | 1.17865e-05 | 3(Loss) | true |
