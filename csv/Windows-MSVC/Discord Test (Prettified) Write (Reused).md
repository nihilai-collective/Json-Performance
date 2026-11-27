
----
### Discord Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11330 | 0.130626 | 827.017ms | 94370 | 30 | 3229.89 | 7943.33 | 0.167574 | 0.217626 | 1(Win) | true |
| Glaze | 3269.94 | 0.109073 | 2774.73ms | 94370 | 2560 | 2.30709e+06 | 27522.9 | 0.4023 | 0.756387 | 2(Loss) | true |
