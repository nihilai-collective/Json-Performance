
----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7284.51 | 0.105005 | 5794.69ms | 6661897 | 80 | 6.70972e+07 | 872163 | 1.63384 | 1(Win) | true |
| Glaze | 3129.3 | 0.966025 | 6416.97ms | 6661897 | 80 | 3.07728e+10 | 2.03025e+06 | 1.89786 | 2(Loss) | true |
| simdjson (reflection) | 269.097 | 1.11347 | 7403.76ms | 6661989 | 30 | 2.07332e+12 | 2.36099e+07 | 4.04585 | 3(Loss) | true |
