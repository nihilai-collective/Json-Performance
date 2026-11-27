
----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14948.7 | 0.162214 | 742.847ms | 108313 | 40 | 5025.64 | 6910 | 0.290276 | 0.202458 | 1(Win) | true |
| Glaze | 3776.06 | 0.680889 | 2742.25ms | 108313 | 4890 | 1.69646e+08 | 27355.3 | 0.830324 | 0.804027 | 2(Loss) | true |
