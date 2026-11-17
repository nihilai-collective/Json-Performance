
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1466.32 | 0.135226 | 9205.34ms | 461466 | 160 | 2.63552e+07 | 300131 | 0.313728 | 1.68823 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1411.66 | 0.20931 | 5020.45ms | 461466 | 30 | 1.27737e+07 | 311751 | 0.389804 | 1.75369 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1405.23 | 0.105746 | 9469.98ms | 461466 | 320 | 3.50966e+07 | 313179 | 0.12259 | 1.76168 | 2(Tie) | true |
| Jsonifier (two-stage) | 1305.12 | 0.146536 | 5344.63ms | 461466 | 80 | 1.95326e+07 | 337201 | 0.168919 | 1.89676 | 4(Loss) | true |
| Glaze | 1232.79 | 0.136222 | 5403.96ms | 461466 | 320 | 7.56733e+07 | 356985 | 0.153095 | 2.00815 | 5(Loss) | true |
