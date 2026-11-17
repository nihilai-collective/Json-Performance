
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1249.66 | 0.712647 | 81.7219ms | 905 | 40 | 969.003 | 690.65 | 0.249177 | 1(Win) | true |
| Glaze | 1141.06 | 0.362545 | 79.6934ms | 905 | 1280 | 9625.34 | 756.382 | 0.451642 | 2(Loss) | true |
| Jsonifier (two-stage) | 297.922 | 0.354959 | 315.922ms | 905 | 1280 | 135350 | 2896.98 | 0.500314 | 3(Loss) | true |
| simdjson (ondemand) | 146.049 | 0.340678 | 565.014ms | 905 | 2560 | 1.0376e+06 | 5909.49 | 0.194902 | 4(Loss) | true |
