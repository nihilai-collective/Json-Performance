
----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18018.1 | 0.471099 | 1153.74ms | 213963 | 80 | 227706 | 11324.8 | 0.0282646 | 1(Win) | true |
| Glaze | 2286.01 | 0.548234 | 8682.46ms | 213963 | 80 | 1.91577e+07 | 89260.8 | 0.693091 | 2(Loss) | true |
| simdjson (reflection) | 340.571 | 0.38496 | 8113.86ms | 213963 | 160 | 8.51166e+08 | 599144 | 1.54377 | 3(Loss) | true |
