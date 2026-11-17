
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7262.06 | 0.170573 | 2442.6ms | 183677 | 1280 | 2.16682e+06 | 24121 | 0.123391 | 1(Win) | true |
| simdjson (stage-1) | 6135.07 | 0.193476 | 3006.49ms | 183677 | 2560 | 7.81201e+06 | 28551.9 | 1.26583 | 2(Loss) | true |
