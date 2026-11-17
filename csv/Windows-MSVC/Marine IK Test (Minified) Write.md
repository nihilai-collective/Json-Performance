
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 843.83 | 0.245217 | 6626.56ms | 1834197 | 30 | 7.75182e+08 | 2.07296e+06 | 0.426972 | 2.93386 | 1(Win) | true |
| Glaze | 571.794 | 0.225607 | 9747.04ms | 1833577 | 160 | 7.61635e+09 | 3.05816e+06 | 0.69386 | 4.3297 | 2(Loss) | true |
