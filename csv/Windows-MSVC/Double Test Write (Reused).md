
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 759.516 | 0.0833033 | 275.272ms | 1997 | 160 | 698.113 | 2507.5 | 0.0996016 | 3.22625 | 1(Win) | true |
| Glaze | 379.15 | 0.103884 | 457.299ms | 1798 | 80 | 1765.82 | 4522.5 | 0.165563 | 6.49311 | 2(Loss) | true |
