
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1402.44 | 0.249169 | 647.036ms | 9578 | 320 | 84278.6 | 6513.12 | 0 | 2.15696 | 1(Win) | true |
| Glaze | 1045.74 | 0.279837 | 876.981ms | 9578 | 2560 | 1.5295e+06 | 8734.73 | 0.0790934 | 2.8978 | 2(Loss) | true |
