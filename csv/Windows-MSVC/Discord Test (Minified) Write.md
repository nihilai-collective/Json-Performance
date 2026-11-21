
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10424.9 | 0.201217 | 525.25ms | 56369 | 30 | 3229.89 | 5156.67 | 0.45045 | 0.236496 | 1(Win) | true |
| Glaze | 3111.88 | 0.0908883 | 1771.95ms | 56369 | 4890 | 1.20548e+06 | 17275 | 0.00254646 | 0.794156 | 2(Loss) | true |
