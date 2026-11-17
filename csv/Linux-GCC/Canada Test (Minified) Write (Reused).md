
----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1769.54 | 0.0673916 | 7044.52ms | 2090234 | 80 | 4.61074e+07 | 1.12651e+06 | 0.111925 | 1.39909 | 1(Win) | true |
| Glaze | 1330.64 | 0.0847016 | 9473.06ms | 2090234 | 160 | 2.57617e+08 | 1.49808e+06 | 0.00657217 | 1.86059 | 2(Loss) | true |
| simdjson (reflection) | 862.531 | 0.103653 | 7209.34ms | 2090326 | 40 | 2.29565e+08 | 2.31121e+06 | 0.0413966 | 2.87039 | 3(Loss) | true |
