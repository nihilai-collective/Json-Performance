
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1166.14 | 0.513624 | 103.13ms | 1213 | 640 | 16614.8 | 992 | 0.879297 | 1(Win) | true |
| Glaze | 795.713 | 0.979265 | 151.03ms | 1213 | 1280 | 259430 | 1453.8 | 0.805131 | 2(Loss) | true |
| simdjson (reflection) | 614.408 | 0.78969 | 191.485ms | 1213 | 2560 | 565928 | 1882.8 | 1.87209 | 3(Loss) | true |
| simdjson (ondemand) | 233.944 | 0.704192 | 499.622ms | 1213 | 640 | 775996 | 4944.8 | 0.993112 | 4(Loss) | true |
