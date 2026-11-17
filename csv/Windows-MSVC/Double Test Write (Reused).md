
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 548.396 | 0.125896 | 326.669ms | 1811 | 160 | 2515.33 | 3149.38 | 0.0595711 | 5.48405 | 1(Win) | true |
| Glaze | 432.537 | 0.129087 | 417.918ms | 1798 | 2560 | 67040.5 | 3964.3 | 0.218272 | 6.99404 | 2(Loss) | true |
