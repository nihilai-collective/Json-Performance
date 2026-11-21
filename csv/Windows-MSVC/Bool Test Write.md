
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 836.393 | 0.269448 | 107.297ms | 905 | 4890 | 37803.9 | 1031.9 | 0.513362 | 2.88117 | 1(Win) | true |
| Glaze | 65.0952 | 1.33544 | 1369.11ms | 905 | 2560 | 8.02585e+07 | 13258.7 | 1.71837 | 37.9457 | 2(Loss) | true |
