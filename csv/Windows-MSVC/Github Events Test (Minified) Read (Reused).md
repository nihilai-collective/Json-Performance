
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1700.25 | 0.219693 | 3987.71ms | 53331 | 640 | 2.76404e+06 | 29913.4 | 0.34356 | 1.78599 | 1(Win) | true |
| Glaze | 1551.21 | 0.979822 | 4451.6ms | 53331 | 40 | 4.1283e+06 | 32787.5 | 0.432736 | 1.95794 | 2(Loss) | true |
| Jsonifier (two-stage) | 1298.89 | 1.50928 | 4693.97ms | 53331 | 1280 | 4.47065e+08 | 39157 | 0.260885 | 2.33831 | 3(Loss) | true |
| simdjson (ondemand) | 914.77 | 0.818412 | 6222.94ms | 53331 | 2560 | 5.30055e+08 | 55599.1 | 0.0840985 | 3.32075 | 4(Loss) | true |
