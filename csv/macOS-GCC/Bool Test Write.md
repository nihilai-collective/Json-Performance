
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1757.95 | 1.48816 | 53.3361ms | 905 | 4890 | 261031 | 490.955 | 1.1169 | 1(Win) | true |
| simdjson (reflection) | 211.663 | 0.624288 | 440.648ms | 905 | 320 | 207362 | 4077.6 | 0.215348 | 2(Loss) | true |
| Glaze | 102.54 | 0.484504 | 769.429ms | 905 | 1280 | 2.12873e+06 | 8417 | 0.550593 | 3(Loss) | true |
