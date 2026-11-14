
----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 806.065 | 0.15126 | 6732.18ms | 1834197 | 30 | 3.23236e+08 | 2.17008e+06 | 0.0951715 | 3.77032 | 1(Win) | true |
| Glaze | 738.35 | 0.165248 | 7314.55ms | 1833577 | 80 | 1.22528e+09 | 2.3683e+06 | 0.0821644 | 4.1162 | 2(Loss) | true |
