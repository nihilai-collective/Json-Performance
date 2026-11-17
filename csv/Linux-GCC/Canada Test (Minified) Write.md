
----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1770.81 | 0.0757918 | 7085.9ms | 2090234 | 40 | 2.91171e+07 | 1.1257e+06 | 0.0269523 | 1.3981 | 1(Win) | true |
| Glaze | 1289.01 | 0.0365151 | 9738.07ms | 2090234 | 320 | 1.0204e+08 | 1.54646e+06 | 0.181881 | 1.92068 | 2(Loss) | true |
| simdjson (reflection) | 876.108 | 0.0638452 | 7115.91ms | 2090326 | 80 | 1.68834e+08 | 2.27539e+06 | 0.316387 | 2.82592 | 3(Loss) | true |
