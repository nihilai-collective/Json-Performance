
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 778.619 | 1.1675 | 5106.56ms | 2251027 | 40 | 4.14464e+10 | 2.75712e+06 | 0.501113 | 1(Win) | true |
| Jsonifier (two-stage) | 709.171 | 0.525068 | 5652.6ms | 2251027 | 40 | 1.01053e+10 | 3.02712e+06 | 1.59172 | 2(Loss) | true |
| simdjson (ondemand) | 610.996 | 0.313568 | 6201.22ms | 2251027 | 40 | 4.85521e+09 | 3.51352e+06 | 0.587302 | 3(Loss) | true |
| Glaze | 558.379 | 0.962436 | 6871.02ms | 2251027 | 80 | 1.09531e+11 | 3.84461e+06 | 0.780794 | 4(Loss) | true |
