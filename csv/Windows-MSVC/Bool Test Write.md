
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1121.47 | 0.118455 | 79.4409ms | 905 | 4890 | 4063.85 | 769.591 | 0.0331539 | 2.64683 | 1(Win) | true |
| Glaze | 86.6158 | 0.264432 | 1052.27ms | 905 | 2560 | 1.77735e+06 | 9964.41 | 0.0560903 | 35.0149 | 2(Loss) | true |
