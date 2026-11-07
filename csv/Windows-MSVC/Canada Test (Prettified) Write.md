
----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2735.72 | 0.128171 | 7296.32ms | 6661897 | 160 | 1.41761e+09 | 2.32235e+06 | 0.0206645 | 0.904946 | 1(Win) | true |
| Glaze | 1460.97 | 0.0835843 | 6613.25ms | 6661897 | 80 | 1.05695e+09 | 4.34869e+06 | 0.0650061 | 1.6946 | 2(Loss) | true |
