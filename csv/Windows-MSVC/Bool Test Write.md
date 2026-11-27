
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1147.9 | 0.527012 | 83.273ms | 905 | 160 | 2512.19 | 751.875 | 0.25 | 2.58497 | 1(Win) | true |
| Glaze | 100.551 | 1.6524 | 967.082ms | 905 | 640 | 1.28746e+07 | 8583.44 | 0.116639 | 30.1523 | 2(Loss) | true |
