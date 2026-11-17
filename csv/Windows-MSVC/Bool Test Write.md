
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1091.48 | 0.420416 | 82.1206ms | 905 | 4890 | 54041.8 | 790.736 | 0.157571 | 2.18903 | 1(Win) | true |
| Glaze | 77.8827 | 0.356008 | 1204.32ms | 905 | 4890 | 7.61106e+06 | 11081.7 | 0.156576 | 31.6847 | 2(Loss) | true |
