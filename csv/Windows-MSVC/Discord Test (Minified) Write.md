
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11177.7 | 0.0605783 | 501.667ms | 56369 | 160 | 1358.1 | 4809.38 | 0.0908855 | 0.219957 | 1(Win) | true |
| Glaze | 3232.76 | 0.093127 | 1690.7ms | 56369 | 4890 | 1.17272e+06 | 16629 | 0.378183 | 0.764404 | 2(Loss) | true |
