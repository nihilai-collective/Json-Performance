
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1130.74 | 0.29597 | 79.1392ms | 905 | 640 | 3266.21 | 763.281 | 0.0204666 | 2.62305 | 1(Win) | true |
| Glaze | 102.659 | 0.425691 | 896.33ms | 905 | 2560 | 3.27894e+06 | 8407.23 | 0.43445 | 29.5307 | 2(Loss) | true |
