
----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1254.34 | 0.077228 | 5023.74ms | 2090234 | 80 | 1.20504e+08 | 1.58921e+06 | 1.69939 | 1.97366 | 1(Win) | true |
| Glaze | 824.5 | 0.247541 | 7451.15ms | 2090234 | 80 | 2.86545e+09 | 2.41771e+06 | 0.4988 | 3.00258 | 2(Loss) | true |
