
----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1326.57 | 0.629347 | 9400.06ms | 2090326 | 160 | 1.43109e+10 | 1.50274e+06 | 0.159505 | 2.29071 | 1(Win) | true |
| Glaze | 776.45 | 0.620762 | 7901.39ms | 2090234 | 160 | 4.06381e+10 | 2.56733e+06 | 0.288498 | 3.91395 | 2(Loss) | true |
