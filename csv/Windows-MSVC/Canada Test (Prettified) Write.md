
----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2685.13 | 0.0657978 | 7349.45ms | 6661897 | 80 | 1.939e+08 | 2.36609e+06 | 0.168085 | 1.13183 | 1(Win) | true |
| Glaze | 1421.67 | 0.620412 | 6690.18ms | 6661897 | 40 | 3.07483e+10 | 4.46889e+06 | 0.81755 | 2.13779 | 2(Loss) | true |
