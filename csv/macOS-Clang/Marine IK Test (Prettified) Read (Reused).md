
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2191.42 | 0.379853 | 5421.35ms | 7351818 | 80 | 1.18157e+10 | 3.1994e+06 | 0.24647 | 1(Win) | true |
| Jsonifier (two-stage) | 2053.41 | 0.380996 | 5764.19ms | 7351818 | 40 | 6.76924e+09 | 3.41444e+06 | 0.242565 | 2(Loss) | true |
| Glaze | 1500.46 | 0.3473 | 7590.67ms | 7351818 | 80 | 2.10688e+10 | 4.67273e+06 | 1.43585 | 3(Loss) | true |
| simdjson (ondemand) | 1428.97 | 0.880854 | 8084.61ms | 7351818 | 40 | 7.47153e+10 | 4.90649e+06 | 0.354705 | 4(Loss) | true |
