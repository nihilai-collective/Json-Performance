
----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26628.7 | 0.0719149 | 486.003ms | 136037 | 30 | 368.276 | 4872 | 0.0335361 | 0.0924778 | 1(Win) | true |
| Glaze | 6257.41 | 0.113918 | 2221.62ms | 136076 | 1280 | 714443 | 20739 | 0.00660699 | 0.395169 | 2(Loss) | true |
| simdjson (reflection) | 602.849 | 0.315685 | 5425.39ms | 136037 | 30 | 1.3846e+07 | 215203 | 0.704701 | 4.10612 | 3(Loss) | true |
