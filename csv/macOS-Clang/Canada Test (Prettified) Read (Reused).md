
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1596.35 | 0.795003 | 5857.61ms | 5373214 | 40 | 2.60503e+10 | 3.21002e+06 | 1.34867 | 1(Win) | true |
| Jsonifier (two-stage) | 1401.27 | 0.474608 | 6673.62ms | 5373214 | 80 | 2.40981e+10 | 3.65688e+06 | 2.29426 | 2(Loss) | true |
| simdjson (ondemand) | 1174.03 | 0.54813 | 7648.84ms | 5373214 | 80 | 4.57897e+10 | 4.36471e+06 | 1.81558 | 3(Loss) | true |
| Glaze DID NOT CONVERGE | 1116.76 | 1.40239 | 7648.71ms | 5373214 | 30 | 1.24226e+11 | 4.58855e+06 | 5.33116 | -(Loss) | false |
