
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1373.76 | 0.10399 | 66.711ms | 905 | 320 | 136.586 | 628.256 | 0.186676 | 1(Win) | true |
| Glaze | 1334.02 | 0.482804 | 69.7169ms | 905 | 2560 | 24977.7 | 646.971 | 0.126331 | 2(Loss) | true |
| simdjson (ondemand) | 283.798 | 0.118227 | 319.267ms | 905 | 80 | 1034.19 | 3041.16 | 0.290616 | 3(Loss) | true |
