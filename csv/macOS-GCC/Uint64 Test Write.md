
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 284.865 | 0.151726 | 411.186ms | 1213 | 2560 | 97186.8 | 4060.9 | 0.288946 | 1(Win) | true |
| simdjson (reflection) | 282.093 | 0.247993 | 414.367ms | 1213 | 1280 | 132381 | 4100.8 | 0.0292711 | 2(Loss) | true |
| Glaze | 180.819 | 0.444739 | 661.892ms | 1213 | 320 | 259057 | 6397.6 | 0.0375 | 3(Loss) | true |
