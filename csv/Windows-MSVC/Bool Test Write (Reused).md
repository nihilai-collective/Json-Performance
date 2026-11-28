
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1455.98 | 0.4994 | 70.7758ms | 905 | 4890 | 42854.4 | 592.781 | 0.0276736 | 1.61768 | 1(Win) | true |
| Glaze | 317.016 | 0.245608 | 180.661ms | 905 | 40 | 1788.46 | 2722.5 | 0.0919118 | 7.72019 | 2(Loss) | true |
