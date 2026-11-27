
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1408.38 | 0.313792 | 96.5049ms | 905 | 320 | 1183.29 | 612.812 | 0.255624 | 1.67808 | 1(Win) | true |
| Glaze | 430.596 | 0.127803 | 208.72ms | 905 | 160 | 1049.92 | 2004.38 | 0.279851 | 5.66918 | 2(Loss) | true |
