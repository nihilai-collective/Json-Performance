
----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10418 | 0.0395117 | 5299.47ms | 500299 | 4890 | 1.60121e+06 | 45797.7 | 0.158978 | 0.488374 | 2.49765 | 0.106702 | 7.09596e-06 | 1.46497e-06 | 6.68312e-07 | 1(Win) | true |
| simdjson (stage-1) | 9493.91 | 0.0645764 | 5736.76ms | 500299 | 640 | 674057 | 50255.6 | 0.0231109 | 0.53381 | 2.79453 | 0.112549 | 2.64061e-05 | 7.81595e-05 | 9.79727e-06 | 2(Loss) | true |
