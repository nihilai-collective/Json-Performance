
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1033.74 | 0.0653175 | 87.4205ms | 905 | 320 | 95.1673 | 834.909 | 0.151359 | 1(Win) | true |
| Glaze | 132.6 | 0.0780012 | 660.718ms | 905 | 80 | 2062.07 | 6508.86 | 0.0719654 | 2(Loss) | true |
