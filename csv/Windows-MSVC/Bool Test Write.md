
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1153.89 | 0.264227 | 78.8434ms | 905 | 640 | 2499.78 | 747.969 | 0.0208855 | 2.06997 | 1(Win) | true |
| Glaze | 81.5662 | 0.40675 | 1131.42ms | 905 | 2560 | 4.74211e+06 | 10581.3 | 0.20086 | 30.2586 | 2(Loss) | true |
