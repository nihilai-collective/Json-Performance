
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 467.733 | 0.149832 | 376.167ms | 1811 | 40 | 1224.36 | 3692.5 | 0.0225632 | 5.20856 | 1(Win) | true |
| Glaze | 139.783 | 0.747285 | 1272.86ms | 1798 | 640 | 5.37799e+06 | 12266.9 | 0.109423 | 17.6658 | 2(Loss) | true |
