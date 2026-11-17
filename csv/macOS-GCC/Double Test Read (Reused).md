
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1075.47 | 0.646484 | 163.769ms | 1811 | 2560 | 275926 | 1605.9 | 0.180911 | 1(Win) | true |
| Glaze | 814.979 | 1.46934 | 190.797ms | 1811 | 320 | 310268 | 2119.2 | 0.637659 | 2(Loss) | true |
| Jsonifier (two-stage) | 507.733 | 1.66244 | 361.715ms | 1811 | 80 | 255829 | 3401.6 | 0.093985 | 3(Loss) | true |
| simdjson (ondemand) | 139.944 | 0.328376 | 1247.18ms | 1811 | 1280 | 2.10224e+06 | 12341.4 | 0.507884 | 4(Loss) | true |
