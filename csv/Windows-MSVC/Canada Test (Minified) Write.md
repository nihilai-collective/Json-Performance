
----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1178 | 0.101231 | 5236.57ms | 2090234 | 160 | 4.69513e+08 | 1.69219e+06 | 0.161997 | 2.57975 | 1(Win) | true |
| Glaze | 843.642 | 0.106855 | 7369.76ms | 2090234 | 80 | 5.09978e+08 | 2.36285e+06 | 0.267602 | 3.60234 | 2(Loss) | true |
