
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 406.99 | 0.0661996 | 914.534ms | 3873 | 2560 | 92401.2 | 9075.35 | 0.0650363 | 7.45008 | 1(Win) | true |
| Glaze | 368.022 | 0.149307 | 1006.11ms | 3873 | 4890 | 1.09803e+06 | 10036.3 | 0.268517 | 8.2397 | 2(Loss) | true |
