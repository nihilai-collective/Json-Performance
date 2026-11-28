
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1440.71 | 0.137953 | 71.6939ms | 905 | 320 | 218.554 | 599.062 | 0.15625 | 1.64214 | 1(Win) | true |
| Glaze | 511.76 | 0.370727 | 184.883ms | 905 | 1280 | 50036.1 | 1686.48 | 0.218199 | 4.75956 | 2(Loss) | true |
