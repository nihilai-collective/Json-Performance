
----
### Discord Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15198.5 | 0.0967439 | 354.781ms | 56369 | 30 | 351.275 | 3537.03 | 0.074395 | 0.161575 | 1(Win) | true |
| simdjson (reflection) | 13216.5 | 0.0590534 | 410.809ms | 56369 | 30 | 173.085 | 4067.47 | 0.211804 | 0.186004 | 2(Loss) | true |
| Glaze | 5381.82 | 0.206448 | 1006.98ms | 56369 | 1280 | 544321 | 9988.75 | 0.229015 | 0.458787 | 3(Loss) | true |
