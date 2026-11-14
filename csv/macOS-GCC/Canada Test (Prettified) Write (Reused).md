
----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6796.57 | 0.451475 | 6014.58ms | 6661897 | 320 | 5.69946e+09 | 934778 | 0.85882 | 1(Win) | true |
| Glaze | 3555.22 | 0.868434 | 5665.75ms | 6661897 | 40 | 9.63377e+09 | 1.78703e+06 | 0.180947 | 2(Loss) | true |
| simdjson (reflection) | 274.914 | 1.29307 | 7305.67ms | 6661989 | 30 | 2.67906e+12 | 2.31104e+07 | 3.21982 | 3(Loss) | true |
