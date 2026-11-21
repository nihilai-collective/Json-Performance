
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2956.16 | 0.276371 | 8182.48ms | 7351818 | 40 | 1.71861e+09 | 2.37174e+06 | 0.805897 | 0.837495 | 1(Win) | true |
| Jsonifier | 2759.81 | 0.101436 | 8771.22ms | 7351818 | 160 | 1.06251e+09 | 2.54048e+06 | 0.949657 | 0.897075 | 2(Loss) | true |
| simdjson (ondemand) | 2532.73 | 0.0531479 | 9429.72ms | 7351818 | 80 | 1.7317e+08 | 2.76825e+06 | 0.287505 | 0.97751 | 3(Loss) | true |
| Glaze | 2298.31 | 0.186234 | 5016.02ms | 7351818 | 30 | 9.68305e+08 | 3.05061e+06 | 1.51765 | 1.07721 | 4(Loss) | true |
