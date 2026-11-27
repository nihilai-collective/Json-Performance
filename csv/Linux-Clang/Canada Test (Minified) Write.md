
----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2039.41 | 0.0352092 | 6160.44ms | 2090326 | 320 | 3.79037e+07 | 977484 | 0.130632 | 1.21394 | 1(Win) | true |
| Glaze | 1032.2 | 0.0384794 | 6163.29ms | 2090234 | 80 | 4.41785e+07 | 1.93122e+06 | 0.066016 | 2.39854 | 2(Loss) | true |
