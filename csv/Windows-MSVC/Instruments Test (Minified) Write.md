
----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14744.5 | 0.232295 | 722.388ms | 108313 | 4890 | 1.29506e+06 | 7005.71 | 0.0456666 | 0.167216 | 1(Win) | true |
| Glaze | 3211.47 | 0.0711651 | 3262.27ms | 108313 | 4890 | 2.5621e+06 | 32164.5 | 0.0459488 | 0.77025 | 2(Loss) | true |
