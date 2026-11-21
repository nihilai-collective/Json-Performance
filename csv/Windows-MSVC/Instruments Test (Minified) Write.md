
----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14791.7 | 0.154799 | 724.857ms | 108313 | 30 | 3505.75 | 6983.33 | 0.0477099 | 0.166983 | 1(Win) | true |
| Glaze | 2945.67 | 0.377089 | 3528.54ms | 108313 | 160 | 2.7977e+06 | 35066.9 | 0.318019 | 0.839653 | 2(Loss) | true |
