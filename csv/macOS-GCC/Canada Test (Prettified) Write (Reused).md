
----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7690.42 | 1.6626 | 6199.69ms | 6661897 | 30 | 5.65969e+09 | 826129 | 2.76082 | 1(Win) | true |
| Glaze | 3287.1 | 1.45319 | 5836.27ms | 6661897 | 30 | 2.36667e+10 | 1.93279e+06 | 1.45148 | 2(Loss) | true |
| simdjson (reflection) | 247.806 | 1.0888 | 7372.22ms | 6661989 | 30 | 2.33778e+12 | 2.56385e+07 | 1.54111 | 3(Loss) | true |
