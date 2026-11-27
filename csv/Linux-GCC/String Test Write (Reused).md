
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4449.23 | 0.051744 | 97.632ms | 4215 | 160 | 34.9676 | 903.469 | 0.293144 | 0.539721 | 1(Win) | true |
| simdjson (reflection) | 3983.68 | 0.0865526 | 108.013ms | 4215 | 40 | 30.5103 | 1009.05 | 0.114099 | 0.60465 | 2(Loss) | true |
| Glaze | 2742.63 | 0.0245952 | 164.754ms | 4215 | 320 | 41.5824 | 1465.65 | 0.196544 | 0.885386 | 3(Loss) | true |
