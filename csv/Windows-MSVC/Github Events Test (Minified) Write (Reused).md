
----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11858.3 | 0.136109 | 480.751ms | 58581 | 80 | 3289.56 | 4711.25 | 0.0795334 | 0.207711 | 1(Win) | true |
| Glaze | 5308.05 | 0.143328 | 1087.76ms | 58581 | 40 | 9102.56 | 10525 | 0.429389 | 0.46499 | 2(Loss) | true |
