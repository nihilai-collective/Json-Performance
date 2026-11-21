
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 438.082 | 0.693456 | 900.737ms | 3873 | 160 | 546942 | 8431.25 | 0.671642 | 5.62613 | 1(Win) | true |
| Glaze | 326.86 | 0.682809 | 1140.27ms | 3873 | 4890 | 2.91125e+07 | 11300.2 | 1.59092 | 7.55106 | 2(Loss) | true |
