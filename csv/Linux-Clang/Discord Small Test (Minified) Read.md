
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2049.02 | 0.242645 | 228.838ms | 4857 | 2560 | 77024.2 | 2260.59 | 0.0304043 | 1.19268 | 1(Win) | true |
| Jsonifier (two-stage) | 1769.85 | 0.210748 | 265.21ms | 4857 | 2560 | 77881.1 | 2617.17 | 0.108536 | 1.38475 | 2(Loss) | true |
| Glaze | 1697.45 | 0.161037 | 276.826ms | 4857 | 160 | 3089.69 | 2728.79 | 0.0858159 | 1.44445 | 3(Loss) | true |
| simdjson (ondemand) | 819.891 | 0.0537126 | 568.156ms | 4857 | 80 | 736.658 | 5649.52 | 0.374437 | 3.00562 | 4(Loss) | true |
