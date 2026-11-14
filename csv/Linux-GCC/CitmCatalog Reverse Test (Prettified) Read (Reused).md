
----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1577.73 | 0.254541 | 9393.59ms | 1151920 | 40 | 1.25648e+08 | 696291 | 0.0517069 | 3.24579 | 15.7936 | 3.18863 | 0.00650384 | 0.031673 | 1.49316e-05 | 1(Win) | true |
| simdjson (ondemand) | 999.654 | 0.0430783 | 7211.57ms | 1151920 | 320 | 7.17153e+07 | 1.09894e+06 | 0.20299 | 5.12528 | 27.8174 | 5.57934 | 0.0110012 | 0.0481709 | 3.36937e-06 | 2(Loss) | true |
