
----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10778.2 | 0.186919 | 539.584ms | 58581 | 30 | 2816.09 | 5183.33 | 0 | 0.228541 | 1(Win) | true |
| Glaze | 4481.93 | 0.126122 | 1316.74ms | 58581 | 80 | 19772.2 | 12465 | 0.776119 | 0.551464 | 2(Loss) | true |
