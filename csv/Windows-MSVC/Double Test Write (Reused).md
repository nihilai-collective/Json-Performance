
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 694.752 | 0.202048 | 296.285ms | 1997 | 80 | 2454.11 | 2741.25 | 0.0456204 | 3.52923 | 1(Win) | true |
| Glaze | 216.412 | 0.144261 | 486.289ms | 1798 | 30 | 3919.54 | 7923.33 | 0.126369 | 11.3852 | 2(Loss) | true |
